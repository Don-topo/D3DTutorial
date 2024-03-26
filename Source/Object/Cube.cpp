#include "Cube.h"

Cube::Cube()
{
	mVertices =
	{
		// Front Face Vertices, Pos + UV
		{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} },
		{ { 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f} },

		// Back Face Vertices, Pos + UV
		{ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f} },
		{ { 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f} },
		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },

		// Left Face Vertices, Pos + UV
		{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f} },
		{ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f} },
		{ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },

		// Right Face Vertices, Pos + UV
		{ { 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f} },
		{ { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} },
		{ { 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f} },
		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },

		// Top Face Vertices, Pos + UV
		{ {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f} },
		{ { 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f} },
		{ {-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} },

		// Bottom Face Vertices Pos + UV
		{ {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f} },
		{ { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} },
		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
	};

	mIndices =
	{
		// Front Face Indices
		0, 1, 3,
		1, 2, 3,

		// Back Face Indices
		7, 5, 4,
		7, 6, 5,

		// Left Face Indices
		10, 9, 8,
		11, 10, 8,

		// Right Face Indices
		12, 13, 14,
		12, 14, 15,

		// Top Face Indices
		18, 17, 16,
		19, 18, 16,

		// Bottom Face Indices
		20, 21, 22,
		20, 22, 23
	};

	InitBuffer();
}

void Cube::Update()
{
	mWorldData.rotation.x += 0.1f;
	mWorldData.rotation.y += 0.1f;
	mWorldData.rotation.z += 0.1f;
}
