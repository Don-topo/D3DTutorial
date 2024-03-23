#pragma once

#include <Renderer/Renderer.h>
#include <exception>

class RendererManager
{
public:
	RendererManager() = default;
	~RendererManager() = default;

	static Renderer* CreateRenderer(Window* pWindow)
	{
		if (mRenderer != nullptr)
		{
			throw std::exception("Renderer is already initialized!\n");
		}
		mRenderer = new Renderer(pWindow);
		return mRenderer;
	}
	static Renderer* GetRenderer()
	{
		if (mRenderer == nullptr) {
			throw std::exception("Renderer is not initialized!\n");
		}

		return mRenderer;
	}

private:
	static inline Renderer* mRenderer = nullptr;

};