#include <Runtime/Window/Window.h>
#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>

int main()
{	
	auto window = std::make_shared<Window>();
	auto device = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc());

	auto swapchain = device->CreateSwapchain(SwapchainDesc(window));

	while (window->IsOpen())
	{
		window->ProcessMessage();
	}
	return 0;
}