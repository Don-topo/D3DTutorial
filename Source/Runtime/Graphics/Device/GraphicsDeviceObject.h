#pragma once

#include <memory>

#include <Runtime/Graphics/Device/DeviceObjectType.h>

class GraphicsDevice;

class RUNTIME_API GraphicsDeviceObject
{
public:
	GraphicsDeviceObject() = default;
	GraphicsDeviceObject(const GraphicsDeviceObject&) = delete;
	GraphicsDeviceObject& operator=(const GraphicsDeviceObject&) = delete;
	virtual ~GraphicsDeviceObject() = default;

	virtual GraphicsDeviceObject GetDeviceType() noexcept = 0;
	std::shared_ptr<GraphicsDevice>& GetOwnerDevice() noexcept { return mOwnerDevice; }

protected:
	std::shared_ptr<GraphicsDevice> mOwnerDevice;

private:

};