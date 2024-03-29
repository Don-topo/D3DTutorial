#include "GraphicsDevice.h"

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Framebuffer/FramebufferDesc.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Graphics/Swapchain/SwapchainDesc.h>

GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc)
{
	DEV_ASSERT(SUCCEEDED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
		&mD3D11Device, nullptr, &mD3D11ImmediateContext)), "GraphicsDevice", "Failed to createD3D11 device");

	DEV_LOG(TE_VERBOSE, "GraphicsDevice", "Created GraphicsDevice successfully.");
}

std::shared_ptr<Swapchain> GraphicsDevice::CreateSwapchain(const SwapchainDesc& desc)
{
	mSwapChain = std::make_shared<Swapchain>(shared_from_this(), desc);
	mDeviceObjects.push_back(mSwapChain);
	return mSwapChain;
}

std::shared_ptr<Framebuffer> GraphicsDevice::CreateFramebuffer(const FramebufferDesc& desc)
{
	auto framebuffer = std::make_shared<Framebuffer>(shared_from_this(), desc);
	mDeviceObjects.push_back(framebuffer);
	return framebuffer;
}
