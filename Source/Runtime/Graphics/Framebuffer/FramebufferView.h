#pragma once

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Framebuffer/FramebufferViewDesc.h>

class FramebufferView : public GraphicsDeviceObject
{
public:
	FramebufferView(std::shared_ptr<GraphicsDevice> device, const FramebufferViewDesc& desc);
	FramebufferView(const FramebufferView&) = delete;
	FramebufferView& operator=(const FramebufferView&) = delete;
	virtual ~FramebufferView() override = default;

	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::FramerbufferView; }

private:

};
