#include "Camera.h"

Camera::Camera(XMFLOAT3 startPosition)
{
	mPosition = startPosition;
	mFront = XMFLOAT3(0, 0, -1);
	mUp = XMFLOAT3(0, 1, 0);
	mRight = XMFLOAT3(1, 0, 0);
}

Camera::Camera()
{
	mPosition = XMFLOAT3(0, 0, 0);
	mFront = XMFLOAT3(0, 0, -1);
	mUp = XMFLOAT3(0, 1, 0);
	mRight = XMFLOAT3(1, 0, 0);
}

XMMATRIX Camera::GetViewMatrix()
{
	XMVECTOR position = XMLoadFloat3(&mPosition);
	XMVECTOR front = XMLoadFloat3(&mFront);
	XMVECTOR up = XMLoadFloat3(&mUp);
	XMVECTOR right = XMLoadFloat3(&mRight);

	XMVECTOR eyeDirection = position * front;
	
	XMMATRIX viewMatrix = XMMatrixLookAtLH(position, eyeDirection, -up);

	return viewMatrix;
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return XMMatrixPerspectiveFovLH(74.0f, 1280.0f/720.0f, 0.1f, 100.0f);
}

void Camera::ProcessTransformPosition(GLFWwindow* window)
{
	float cameraSpeed = 0.1f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		mPosition = { mPosition.x, mPosition.y, mPosition.z + cameraSpeed };
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mPosition = { mPosition.x, mPosition.y, mPosition.z - cameraSpeed };
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mPosition = { mPosition.x - cameraSpeed, mPosition.y, mPosition.z };
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mPosition = { mPosition.x + cameraSpeed, mPosition.y, mPosition.z };
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		mPosition = { mPosition.x, mPosition.y + cameraSpeed, mPosition.z };
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		mPosition = { mPosition.x, mPosition.y - cameraSpeed, mPosition.z };
}

void Camera::ProcessLookPosition(float xOffset, float yOffset)
{
}
