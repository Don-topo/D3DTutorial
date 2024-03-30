#include <Runtime/Window/Window.h>
#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Graphics/Framebuffer/Framebuffer.h>

#include <Runtime/Graphics/Shader/Shader.h>

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

	const float clearColor[] = { 0.5f, 0.2f, 0.6f, 1.0f };

	ShaderDesc shaderDesc = {};
	shaderDesc.Type = ShaderType::VERTEX_SHADER;
	shaderDesc.EntryPoint = "vs_main";
	shaderDesc.ShaderName = "ObjectVertexShader";
	shaderDesc.ShaderModel = "vs_5_0";

	auto shader = device->CreateShader(shaderDesc);

	while (window->IsOpen())
	{
		window->ProcessMessage();
		device->GetD3D11ImmediateContext()->ClearDepthStencilView(framebuffer->GetDepthTextureView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		device->GetD3D11ImmediateContext()->ClearRenderTargetView(framebuffer->GetColorTextureView().Get(), clearColor);
		swapchain->Present();
	}

	return 0;
}