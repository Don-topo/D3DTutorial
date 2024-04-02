#pragma once

#include <Runtime/Core/Core.h>
#include <DirectXMath.h>
using namespace DirectX;

#include <vector>
#include <memory>

class GraphicsBuffer;
class GraphicsDevice;
class CommandList;

class Mesh
{
public:
	Mesh() = default;
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	~Mesh() = default;

	void AllocateVertex();
	void AllocateIndex();

	std::shared_ptr<GraphicsBuffer> GetPositionBuffer() noexcept { return mPositionBuffer; }
	std::shared_ptr<GraphicsBuffer> GetNormalBuffer() noexcept { return mNormalBuffer; }
	std::shared_ptr<GraphicsBuffer> GetTangentBuffer() noexcept { return mTangentBuffer; }
	std::shared_ptr<GraphicsBuffer> GetBinormalBuffer() noexcept { return mBinormalBuffer; }
	std::shared_ptr<GraphicsBuffer> GetTexCoordBuffer() noexcept { return mTexCoordBuffer; }
	std::shared_ptr<GraphicsBuffer> GetIndexBuffer() noexcept { return mIndexBuffer; }

	std::vector<XMFLOAT3>& GetPositions() noexcept { return mPositions; }
	std::vector<XMFLOAT3>& GetNormals() noexcept { return mNormals; }
	std::vector<XMFLOAT3>& GetTangents() noexcept { return mTangents; }
	std::vector<XMFLOAT3>& GetBinormals() noexcept { return mBinormals; }
	std::vector<XMFLOAT2>& GetTexCoords() noexcept { return mTexCoords; }
	std::vector<uint16>& GetIndices() noexcept { return mIndices; }

private:
	std::vector<XMFLOAT3> mPositions;
	std::vector<XMFLOAT3> mNormals;
	std::vector<XMFLOAT3> mTangents;
	std::vector<XMFLOAT3> mBinormals;
	std::vector<XMFLOAT2> mTexCoords;
	std::vector<uint16> mIndices;

	std::shared_ptr<GraphicsBuffer> mPositionBuffer;
	std::shared_ptr<GraphicsBuffer> mNormalBuffer;
	std::shared_ptr<GraphicsBuffer> mTangentBuffer;
	std::shared_ptr<GraphicsBuffer> mBinormalBuffer;
	std::shared_ptr<GraphicsBuffer> mTexCoordBuffer;
	std::shared_ptr<GraphicsBuffer> mIndexBuffer;

	CommandList* mCommandList;

};