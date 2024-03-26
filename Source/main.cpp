#include "Window/Window.h"
#include "Renderer/RendererManager.h"

#include "Object/Object.h"
#include "Object/Camera.h"

#include <vector>

std::vector<VertexData> vertices =
{
	{ {-0.5f, -0.5f, -0.5f}, { 1.0f, 0.0f, 0.0f, 1.0f} },
	{ {-0.5f, 0.5f, -0.5f},  { 0.0f, 1.0f, 0.0f, 1.0f} },
	{ {0.5f, 0.5f, -0.5f},   { 0.0f, 0.0f, 1.0f, 1.0f} },
	{ {0.5f, -0.5f, -0.5f},  { 1.0f, 1.0f, 0.0f, 1.0f} },

	{ {-0.5f, -0.5f, 0.5f}, { 1.0f, 1.0f, 1.0f, 1.0f} },
	{ {-0.5f,  0.5f, 0.5f}, { 0.0f, 1.0f, 1.0f, 1.0f} },
	{ {0.5f,   0.5f, 0.5f}, { 1.0f, 0.0f, 1.0f, 1.0f} },
	{ {0.5f,  -0.5f, 0.5f}, { 0.5f, 0.5f, 0.5f, 1.0f} }
};

std::vector<uint32_t> indices =
{
	0, 1, 3,
	1, 2, 3,

	7, 5, 4,
	7, 6, 5,

	4, 5, 1,
	4, 1, 0,

	3, 2, 6,
	3, 6, 7,

	1, 5, 6,
	1, 6, 2,

	0, 3, 7,
	0, 7, 4
};


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

	Object* cube = new Object(vertices, indices);
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
			object->UpdateMatrix(basicCamera->GetViewMatrix(), basicCamera->GetProjectionMatrix());
			basicRenderer->Draw(object->GetIndexCount());
		}

		basicRenderer->Present();
	}

	delete basicWindow;
	delete basicRenderer;

	return 0;
}