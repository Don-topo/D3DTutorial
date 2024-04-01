#include <Runtime/Window/Window.h>
#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Sampler/Sampler.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Command/CommandList.h>

#include <DirectXMath.h>
using namespace DirectX;

struct VertexData
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

std::vector<VertexData> triangle = {
	{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
	{ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
	{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
};

std::vector<uint32> indices = {
	0, 1, 2
};


int main()
{	
	auto window = std::make_shared<Window>();
	auto device = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc());

	SwapchainDesc swapchainDesc = {};
	swapchainDesc.Window = window;
	swapchainDesc.SwapchainFormat = TextureFormat::RGBA8_UNSIGNED_NORMALIZED;
	swapchainDesc.BufferCount = 1;
	swapchainDesc.TargetFramerate = 60;

	auto swapchain = device->CreateSwapchain(swapchainDesc);

	FramebufferDesc framebufferDesc = {};
	framebufferDesc.ColorAttachmentFormat = swapchainDesc.SwapchainFormat;
	framebufferDesc.pColorAttachment = swapchain->GetBackTexture();

	auto framebuffer = device->CreateFramebuffer(framebufferDesc);

	ShaderDesc vertexShaderDesc = {};
	vertexShaderDesc.Type = ShaderType::VERTEX_SHADER;
	vertexShaderDesc.EntryPoint = "vs_main";
	vertexShaderDesc.ShaderName = "ObjectVertexShader";
	vertexShaderDesc.ShaderModel = "vs_5_0";

	auto vertexShader = device->CreateShader(vertexShaderDesc);

	ShaderDesc pixelShaderDesc = {};
	pixelShaderDesc.Type = ShaderType::PIXEL_SHADER;
	pixelShaderDesc.EntryPoint = "ps_main";
	pixelShaderDesc.ShaderName = "ObjectPixelShader";
	pixelShaderDesc.ShaderModel = "ps_5_0";

	auto pixelShader = device->CreateShader(pixelShaderDesc);

	SamplerDesc samplerDesc = {};
	samplerDesc.Filter = SamplerFilter::MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = AddressMode::WRAP;
	samplerDesc.AddressV = AddressMode::WRAP;
	samplerDesc.AddressW = AddressMode::WRAP;
	samplerDesc.SamplerComparison = SamplerComparison::ALWAYS;
	samplerDesc.MipLODBias = 1.0f;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = FloatMax;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;

	auto sampler = device->CreateSampler(samplerDesc);

	InputLayoutDesc inputDesc = {};
	inputDesc.SemanticNames = { SemanticName::Position, SemanticName::Color };
	inputDesc.InputFormats = { TextureFormat::RGB32_FLOAT, TextureFormat::RGB32_FLOAT };
	inputDesc.SemanticIndices = { 0, 0 };
	inputDesc.InputSlotIndices = { 0, 0 };
	inputDesc.AlignedByteOffsets = { D3D11_APPEND_ALIGNED_ELEMENT, D3D11_APPEND_ALIGNED_ELEMENT };
	inputDesc.SlotClasses = { SlotClass::PerVertexData, SlotClass::PerVertexData };
	inputDesc.InstanceDataSteps = { 0, 0 };
	inputDesc.PrimitiveMode = PrimitiveMode::TriangleList;

	RasterizerDesc rasterizerDesc = {};
	rasterizerDesc.FillMode = FillMode::Solid;
	rasterizerDesc.CullMode = CullMode::Back;
	rasterizerDesc.FaceOrdering = FaceOrdering::Clockwise;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthClamp = 0.0f;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
	rasterizerDesc.DepthClipEnabled = false;
	rasterizerDesc.ScissorEnabled = false;
	rasterizerDesc.MultisampleEnabled = true;
	rasterizerDesc.AntialiasedLineEnabled = true;

	DepthStencilDesc depthDesc = {};
	depthDesc.DepthEnable = true;
	depthDesc.DepthMask = DepthMask::All;
	depthDesc.DepthCompFunc = DepthStencilComparisonFunc::Less;
	depthDesc.StencilEnable = false;
	depthDesc.StencilReadMask = 0xFF;
	depthDesc.StencilWriteMask = 0xFF;

	BlenderStateDesc blendDesc = {};
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = true;
	blendDesc.RenderTargetBlendDescs = {
		.BlendEnable = false,
		.SrcBlend = BlendType::One,
		.DestBlend = BlendType::One,
		.BlendOp = BlendOperation::Add,
		.SrcBlendAlpha = BlendType::One,
		.DestBlendAlpha = BlendType::One,
		.BlendOpAlpha = BlendOperation::Add,
		.WriteMask = ColorMask::All
	};

	PipelineDesc pipelineDesc = {};
	pipelineDesc.Shaders = { vertexShader, pixelShader };
	pipelineDesc.InputLayout = inputDesc;
	pipelineDesc.Rasterizer = rasterizerDesc;
	pipelineDesc.DepthStencil = depthDesc;
	pipelineDesc.Blend = blendDesc;
	pipelineDesc.Sampler = sampler;

	auto pipeline = device->CreatePipeline(pipelineDesc);

	GraphicsBufferDesc vertexBufferDesc = {};
	vertexBufferDesc.Usage = BufferUsage::VERTEX_BUFFER;
	vertexBufferDesc.SizeInBytes = sizeof(VertexData) * triangle.size();
	vertexBufferDesc.StructureByteStride = sizeof(VertexData);
	vertexBufferDesc.InitialData = triangle.data();
	vertexBufferDesc.CPUAccess = BufferCPUAccess::NONE;
	vertexBufferDesc.ResourceUsage = ResourceUsage::DEFAULT;
	vertexBufferDesc.MiscFlags = 0;

	auto vertexBuffer = device->CreateGraphicsBuffer(vertexBufferDesc);

	GraphicsBufferDesc indexBufferDesc = {};
	indexBufferDesc.Usage = BufferUsage::INDEX_BUFFER;
	indexBufferDesc.SizeInBytes = sizeof(uint32) * indices.size();
	indexBufferDesc.StructureByteStride = sizeof(uint32);
	indexBufferDesc.InitialData = indices.data();
	indexBufferDesc.CPUAccess = BufferCPUAccess::NONE;
	indexBufferDesc.ResourceUsage = ResourceUsage::DEFAULT;
	indexBufferDesc.MiscFlags = 0;

	auto indexBuffer = device->CreateGraphicsBuffer(indexBufferDesc);

	auto commandList = device->CreateCommandList();

	while (window->IsOpen())
	{
		window->ProcessMessage();
		
		commandList->BindFrameBuffer(framebuffer);
		commandList->BindPipeline(pipeline);
		commandList->BindVertexBuffer({ vertexBuffer });
		commandList->BindIndexBuffer(indexBuffer);
		commandList->BindViewPort(window->GetWindowSize());

		const XMFLOAT3 clearColor = { 0.2f, 0.3f, 0.5f };
		commandList->ClearBuffer(framebuffer, clearColor);

		commandList->DrawIndexed(indices.size(), 0, 0);

		device->ExecuteCommandLists({ commandList });
		device->Present();

	}

	return 0;
}