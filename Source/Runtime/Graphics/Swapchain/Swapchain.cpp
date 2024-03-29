#include "Swapchain.h"

#include <Runtime/Window/Window.h>
#include <Runtime/Graphics/Device/GraphicsDevice.h>

#include <Runtime/Graphics/Texture/TextureUtils.h>

Swapchain::Swapchain(std::shared_ptr<GraphicsDevice> device, const SwapchainDesc& desc)
{
	mOwnerDevice = device;

	DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
	swapchainDesc.BufferDesc.Width = desc.Window->GetWindowSize().x;
	swapchainDesc.BufferDesc.Height = desc.Window->GetWindowSize().y;
	swapchainDesc.BufferDesc.Format = TextureUtils::GetTextureFormat(desc.SwapchainFormat);
	swapchainDesc.BufferDesc.RefreshRate.Numerator = desc.TargetFramerate;
	swapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapchainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapchainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.BufferCount = desc.BufferCount;
	swapchainDesc.OutputWindow = desc.Window->GetNativeWindowHandle();
	swapchainDesc.Windowed = !desc.Window->IsFullScreen();
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDesc.Flags = 0;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device().As(&mDXGIDevice)), "Swapchain", "Failed to get D3D11Devjce as DXGIDevice");
	DEV_ASSERT(SUCCEEDED(mDXGIDevice->GetAdapter(&mDXGIAdapter)), "Swapchain", "Failed to get adapter from DXGIDevice");
	DEV_ASSERT(SUCCEEDED(mDXGIAdapter->GetParent(IID_PPV_ARGS(&mDXGIFactory))), "Swapchain", "Failed to get factory from adapter");
	DEV_ASSERT(SUCCEEDED(mDXGIFactory->CreateSwapChain(device->GetD3D11Device().Get(), &swapchainDesc, &mSwapchain)), "Swapchain", "Failed to create swapchain");

	DEV_ASSERT(SUCCEEDED(mSwapchain->GetBuffer(0, IID_PPV_ARGS(&mBackBuffer))), "Swapchain", "Failed to get backbuffer from swapchain");

	DEV_LOG(TE_VERBOSE, "Swapchain", "Created swapchain successfully.");
}

void Swapchain::Present()
{
	mSwapchain->Present(1, 0);
}
