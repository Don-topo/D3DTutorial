#include "Window/Window.h"
#include "Renderer/RendererManager.h"

#include "Object/Camera.h"
#include "Object/Cube.h"

#include <vector>

int main()
{
	// OBJECTS ARRAY
	std::vector<Object*> objects;

	// BASIC WINDOW INITIALIZATION
	Window* basicWindow = new Window({ 1280, 720 }, "Basic Window");	
	basicWindow->Inicialize();

	// BASIC RENDERER INITIALIZATION
	Renderer* basicRenderer = RendererManager::CreateRenderer(basicWindow);

	Camera* basicCamera = new Camera({ 0.0f, 0.0f, 3.0f }, { basicWindow->GetSize().X, basicWindow->GetSize().Y });

	Cube* cube = new Cube();
	objects.push_back(cube);


	// BASIC RENDER LOOP
	while (basicWindow->IsVisible())
	{
		basicWindow->Run();
		basicRenderer->ClearColor({ 0.5f, 0.2f, 0.6f, 1.0f });

		basicCamera->HandleInputs(basicWindow->GetWindowhandler());
		basicCamera->UpdateMatrix();

		basicRenderer->SetPipeline();

		for (auto& object : objects)
		{
			object->SetProps();
			object->Update();
			object->UpdateMatrix(basicCamera->GetViewMatrix(), basicCamera->GetProjectionMatrix());
			basicRenderer->Draw(object->GetIndexCount());
		}

		basicRenderer->Present();
	}

	delete basicWindow;
	delete basicRenderer;

	return 0;
}