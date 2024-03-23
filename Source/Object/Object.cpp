#include "Object.h"

Object::Object(std::vector<VertexData> pArrayVertexData, std::vector<uint32_t> indexData)
{
	mIndexCount = indexData.size();

	mWorldData =
	{
		.position = { 0.0f, 0.0f, 0.0f },
		.rotation = { 0.0f, 0.0f, 0.0f },
		.scale = { 1.0f, 1.0f, 1.0f }
	};

	mTransformData =
	{
		.world = XMMatrixIdentity(),
		.view = XMMatrixIdentity(),
		.projection = XMMatrixIdentity()
	};

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexData) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
	vertexSubresourceData.pSysMem = pArrayVertexData.data();
	vertexSubresourceData.SysMemPitch = 0;
	vertexSubresourceData.SysMemSlicePitch = 0;

	RendererManager::GetRenderer()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, mVertexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint32_t) * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
	indexSubresourceData.pSysMem = indexData.data();
	indexSubresourceData.SysMemPitch = 0;
	indexSubresourceData.SysMemSlicePitch = 0;

	RendererManager::GetRenderer()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexSubresourceData, mIndexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(TransformData);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA constantSubresourceData = {};
	constantSubresourceData.pSysMem = &mTransformData;

	RendererManager::GetRenderer()->GetDevice()->CreateBuffer(&constantBufferDesc, &constantSubresourceData, mConstantBuffer.GetAddressOf());
}

void Object::SetProps()
{
	uint32_t stride = sizeof(VertexData);
	uint32_t offset = 0;

	RendererManager::GetRenderer()->GetDeviceContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
	RendererManager::GetRenderer()->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	RendererManager::GetRenderer()->GetDeviceContext()->VSSetConstantBuffers(0, 1, mConstantBuffer.GetAddressOf());
}

void Object::UpdateMatrix(XMMATRIX view, XMMATRIX projection)
{
	mTransformData.world = XMMatrixTranspose(XMMatrixScaling(mWorldData.scale.x, mWorldData.scale.y, mWorldData.scale.z) *
		XMMatrixRotationRollPitchYaw(XMConvertToRadians(mWorldData.rotation.x), XMConvertToRadians(mWorldData.rotation.y), XMConvertToRadians(mWorldData.rotation.z)) *
		XMMatrixTranslation(mWorldData.position.x, mWorldData.position.y, mWorldData.position.z));

	mTransformData.view = XMMatrixTranspose(view);
	mTransformData.projection = XMMatrixTranspose(projection);

	// Map data
	D3D11_MAPPED_SUBRESOURCE mappedSubresource = {};
	RendererManager::GetRenderer()->GetDeviceContext()->Map(mConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	memcpy(mappedSubresource.pData, &mTransformData, sizeof(TransformData));
	RendererManager::GetRenderer()->GetDeviceContext()->Unmap(mConstantBuffer.Get(), 0);
}
