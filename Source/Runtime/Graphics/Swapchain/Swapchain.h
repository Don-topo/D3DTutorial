#pragma once

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Swapchain/SwapchainDesc.h>

#include <d3d11.h>
#include <dxgi.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Swapchain : public GraphicsDeviceObject
{
public:
	Swapchain(std::shared_ptr<GraphicsDevice> device, const SwapchainDesc& desc);
	virtual ~Swapchain() override = default;

	void Present();

	ComPtr<ID3D11Texture2D> GetBackBuffer() { return mBackBuffer; }
	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Swapchain; }

private:
	ComPtr<ID3D11Texture2D> mBackBuffer;
	ComPtr<IDXGISwapChain> mSwapchain;

	ComPtr<IDXGIDevice> mDXGIDevice;
	ComPtr<IDXGIAdapter> mDXGIAdapter;
	ComPtr<IDXGIFactory> mDXGIFactory;
};