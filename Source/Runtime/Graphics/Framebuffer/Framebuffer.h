#pragma once

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Framebuffer/FramebufferDesc.h>

class Framebuffer : public GraphicsDeviceObject
{
public:
	Framebuffer(std::shared_ptr<GraphicsDevice> device, const FramebufferDesc& desc);
	Framebuffer(const Framebuffer&) = delete;
	Framebuffer& operator=(const Framebuffer&) = delete;
	virtual ~Framebuffer() override = default;

	virtual DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Framebuffer; }

private:

};
