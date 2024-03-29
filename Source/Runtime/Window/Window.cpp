#include "Window.h"

Window::Window()
{
	mWindowSize = { 1280, 720 };
	mPosition = { 0, 0 };
	mTitle = "Rendering Engine";
	mIsFullScreen = false;
	DEV_ASSERT(glfwInit(), "Window", "Failed to initialize GLFW.");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	/*if (mIsFullScreen) {
		mWindow = glfwCreateWindow(mWindowSize.x, mWindowSize.y, mTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	}
	else
	{*/
		mWindow = glfwCreateWindow(mWindowSize.x, mWindowSize.y, mTitle.c_str(), nullptr, nullptr);
	//}
}

void Window::ProcessMessage()
{
	//glfwSwapBuffers(mWindow);
	glfwPollEvents();
}
