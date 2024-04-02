#include <Runtime/Window/Window.h>
#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Sampler/Sampler.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/Resources/ResourceImporter.h>
#include <Runtime/Resources/Mesh/Mesh.h>
#include <Runtime/Resources/Texture/TextureResource.h>
#include <Runtime/Graphics/GraphicsManager.h>


struct CBData
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;
};

int main()
{	
	auto window = std::make_shared<Window>();
	auto device = GraphicsManager::GetInstance().GetMainDevice();

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
	inputDesc.SemanticNames = { SemanticName::Position, SemanticName::TexCoord, SemanticName::Normal };
	inputDesc.InputFormats = { TextureFormat::RGB32_FLOAT, TextureFormat::RGB32_FLOAT, TextureFormat::RGB32_FLOAT };
	inputDesc.SemanticIndices = { 0, 0, 0 };
	inputDesc.InputSlotIndices = { 0, 1, 2 };
	inputDesc.AlignedByteOffsets = { D3D11_APPEND_ALIGNED_ELEMENT, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_APPEND_ALIGNED_ELEMENT };
	inputDesc.SlotClasses = { SlotClass::PerVertexData, SlotClass::PerVertexData, SlotClass::PerVertexData };
	inputDesc.InstanceDataSteps = { 0, 0, 0 };
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

	auto commandList = device->CreateCommandList();

	auto testMesh = std::make_shared<Mesh>();
	auto testColor = std::make_shared<TextureResource>();
	auto testNormal = std::make_shared<TextureResource>();
	ResourceImporter::ReadStaticMeshFile(R"(C:\Users\ruben\Documents\UOC\TFM\Directx12Course\glTF-Sample-Models\2.0\DamagedHelmet\glTF\DamagedHelmet.gltf)", testMesh);
	ResourceImporter::ReadTextureFile(R"(C:\Users\ruben\Documents\UOC\TFM\Directx12Course\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_albedo.jpg)", testColor);
	ResourceImporter::ReadTextureFile(R"(C:\Users\ruben\Documents\UOC\TFM\Directx12Course\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_normal.jpg)", testNormal);

	CBData modelMatrix = {
		.World = XMMatrixIdentity(),
		.View = XMMatrixIdentity(),
		.Projection = XMMatrixIdentity()
	};
	GraphicsBufferDesc cbDesc = {};
	cbDesc.ResourceUsage = ResourceUsage::DYNAMIC;
	cbDesc.CPUAccess = BufferCPUAccess::WRITE;
	cbDesc.Usage = BufferUsage::CONSTANT_BUFFER;
	cbDesc.SizeInBytes = sizeof(CBData);
	cbDesc.StructureByteStride = sizeof(XMMATRIX);
	cbDesc.MiscFlags = 0;
	cbDesc.InitialData = &modelMatrix;

	auto cb = device->CreateGraphicsBuffer(cbDesc);

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 90.0f, 0.0f, 0.0f };
	XMFLOAT3 scale = { 1.0f,1.0f, 1.0 };

	while (window->IsOpen())
	{
		window->ProcessMessage();

		rot.y += 0.1f;

		modelMatrix.World = XMMatrixTranspose(XMMatrixScaling(scale.x, scale.y, scale.z) * 
			XMMatrixRotationRollPitchYaw(XMConvertToRadians(rot.x), XMConvertToRadians(rot.y), XMConvertToRadians(rot.z)) * XMMatrixTranslation(pos.x, pos.y, pos.z));
		modelMatrix.View = XMMatrixTranspose(XMMatrixLookAtLH({ 0.0f, 0.0f, -3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
		modelMatrix.Projection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XMConvertToRadians(74.0f), 
			(float)window->GetWindowSize().x / (float)window->GetWindowSize().y, 0.1f, 100.0f));
		
		commandList->BindFrameBuffer(framebuffer);
		commandList->BindPipeline(pipeline);
		commandList->BindVertexBuffer({ testMesh->GetPositionBuffer(), testMesh->GetTexCoordBuffer(), testMesh->GetNormalBuffer()});
		commandList->BindIndexBuffer({ testMesh->GetIndexBuffer()});
		commandList->BindViewPort(window->GetWindowSize());

		commandList->UpdateDynamicBuffer(cb, &modelMatrix, sizeof(CBData));
		commandList->BindResources({ testColor->GetTextureView(), testNormal->GetTextureView()}, { sampler }, {}, ShaderStage::PixelShader);
		commandList->BindResources({}, {}, { cb }, ShaderStage::VertexShader);

		const XMFLOAT3 clearColor = { 0.2f, 0.3f, 0.5f };
		commandList->ClearBuffer(framebuffer, clearColor);

		commandList->DrawIndexed(testMesh->GetIndices().size(), 0, 0);

		device->ExecuteCommandLists({ commandList });
		device->Present();

	}

	return 0;
}