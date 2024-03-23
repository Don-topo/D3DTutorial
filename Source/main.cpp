#include "Window/Window.h"
#include "Renderer/RendererManager.h"
#include "Object/Object.h"
#include <vector>

std::vector<VertexData> vertices1 =
{
	{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) }
};

std::vector<VertexData> vertices2 =
{
	{ XMFLOAT3(0.5f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.7f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.9f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) }
};

std::vector<uint32_t> indices1 =
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

	Object* triangle = new Object(vertices1, indices1);
	objects.push_back(triangle);

	Object* triangle2 = new Object(vertices2, indices1);
	objects.push_back(triangle2);

	// BASIC RENDER LOOP
	while (basicWindow->IsVisible())
	{
		basicWindow->Run();
		basicRenderer->ClearColor({ 0.5f, 0.2f, 0.6f, 1.0f });
		basicRenderer->SetPipeline();

		for (auto& object : objects)
		{
			object->SetProps();
			basicRenderer->Draw(object->GetIndexCount());
		}

		basicRenderer->Present();
	}

	delete basicWindow;
	delete basicRenderer;

	return 0;
}