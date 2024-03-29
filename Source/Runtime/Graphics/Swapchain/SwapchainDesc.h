#pragma once

#include <Runtime/Core/Core.h>
#include <memory>

class Window;

struct SwapchainDesc
{
	std::shared_ptr<Window> Window;
};