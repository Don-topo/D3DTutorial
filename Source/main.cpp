#include "Window/Window.h"
#include "Renderer/RendererManager.h"
#include "Object/Object.h"
#include "Object/Camera.h"
#include <vector>

std::vector<VertexData> vertices =
{
	{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) }
};

std::vector<uint32_t> indices =
{
	0, 1, 2
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
	Camera* basicCamera = new Camera({ 0.0f, 0.0f, -3.0f });

	Object* triangle = new Object(vertices, indices);
	objects.push_back(triangle);

	Object* triangle2 = new Object(vertices, indices);
	triangle2->SetPosition({ 3.0f, 2.0f, 0.0f });
	objects.push_back(triangle2);

	// BASIC RENDER LOOP
	while (basicWindow->IsVisible())
	{
		basicWindow->Run();
		basicRenderer->ClearColor({ 0.5f, 0.2f, 0.6f, 1.0f });
		basicCamera->ProcessTransformPosition(basicWindow->GetWindowhandler());
		basicRenderer->SetPipeline();

		for (auto& object : objects)
		{
			object->SetProps();
			object->UpdateMatrix(basicCamera->GetViewMatrix(), basicCamera->GetProjectionMatrix());
			basicRenderer->Draw(object->GetIndexCount());
		}

		basicRenderer->Present();
	}

	delete basicCamera;
	delete basicWindow;
	delete basicRenderer;

	return 0;
}