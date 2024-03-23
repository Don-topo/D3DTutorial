#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct VertexData
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

struct WorldData
{
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
};

struct TransformData
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};