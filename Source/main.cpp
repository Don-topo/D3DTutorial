#include "Window/Window.h"
#include "Renderer/Renderer.h"

int main()
{
	Window* basicWindow = new Window({ 1280, 720 }, "Basic Window");	
	basicWindow->Inicialize();

	Renderer* basicRenderer = new Renderer(basicWindow);

	while (basicWindow->IsVisible())
	{
		basicWindow->Run();
		basicRenderer->ClearColor({ 0.5f, 0.2f, 0.6f, 1.0f });
		basicRenderer->Present();
	}

	delete basicWindow;
	delete basicRenderer;

	return 0;
}