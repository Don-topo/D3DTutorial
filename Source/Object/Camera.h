#pragma once

#include <GLFW/glfw3.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera(XMFLOAT3 startPosition);
	Camera();
	~Camera() = default;

	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();

	void ProcessTransformPosition(GLFWwindow* window);
	void ProcessLookPosition(float xOffset, float yOffset);

private:
	XMFLOAT3 mPosition;
	XMFLOAT3 mFront;
	XMFLOAT3 mUp;
	XMFLOAT3 mRight;
};