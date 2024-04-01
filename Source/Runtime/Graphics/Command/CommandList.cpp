#include "CommandList.h"

#include <Runtime/Graphics/Device/GraphicsDevice.h>
#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Graphics/Sampler/Sampler.h>

CommandList::CommandList(std::shared_ptr<GraphicsDevice> device)
{
	mOwnerDevice = device;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateDeferredContext(0, mDeferredContext.GetAddressOf())), "CommandList", "Failed to create deferred context.");
}

void CommandList::BindFrameBuffer(std::shared_ptr<Framebuffer> frameBuffer)
{
	mDeferredContext->OMSetRenderTargets(1, frameBuffer->GetColorTextureView().GetAddressOf(), frameBuffer->GetDepthTextureView().Get());
}

void CommandList::BindPipeline(std::shared_ptr<Pipeline> pipeline)
{
	for (auto& shader : pipeline->GetShaders())
	{
		switch (shader->GetShaderType())
		{
		case ShaderType::VERTEX_SHADER:
			mDeferredContext->VSSetShader(shader->GetVertexShader().Get(), nullptr, 0);
			break;
		case ShaderType::PIXEL_SHADER:
			mDeferredContext->PSSetShader(shader->GetPixelShader().Get(), nullptr, 0);
			break;
		default:
			DEV_ASSERT(false, "CommandList", "Invalid shader type.");
			break;
		}
	}

	mDeferredContext->IASetInputLayout(pipeline->GetInputLayoutObject().Get());
	float factor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	mDeferredContext->OMSetBlendState(pipeline->GetBlendObject().Get(), factor, D3D11_APPEND_ALIGNED_ELEMENT);
	mDeferredContext->OMSetDepthStencilState(pipeline->GetDepthStencilObject().Get(), 0);
	mDeferredContext->RSSetState(pipeline->GetRasterizerObject().Get());
	mDeferredContext->IASetPrimitiveTopology(pipeline->GetPrimitiveTopology());
}

void CommandList::BindViewPort(XMUINT2 windowSize)
{
	D3D11_VIEWPORT viewPort;
	viewPort.Width = (float)windowSize.x;
	viewPort.Height = (float)windowSize.y;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	mDeferredContext->RSSetViewports(1, &viewPort);
}

void CommandList::BindVertexBuffer(const std::vector<std::shared_ptr<GraphicsBuffer>>& vertexBuffer)
{
	for (uint32 i = 0; i < vertexBuffer.size(); i++)
	{
		uint32 stride = vertexBuffer[i]->GetStructureByteStride();
		uint32 offset = 0;
		mDeferredContext->IASetVertexBuffers(i, 1, vertexBuffer[i]->GetBuffer().GetAddressOf(), &stride, &offset);
	}
}

void CommandList::BindIndexBuffer(std::shared_ptr<GraphicsBuffer>& indexBuffer)
{
	mDeferredContext->IASetIndexBuffer(indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CommandList::DrawIndexed(uint32 indexCount, uint32 indexOffset, uint32 vertexOffset)
{
	mDeferredContext->DrawIndexed(indexCount, indexOffset, vertexOffset);
}

void CommandList::ClearBuffer(std::shared_ptr<Framebuffer> framebuffer, XMFLOAT3 color)
{
	float frameColor[] = { color.x, color.y, color.z, 1.0f };
	mDeferredContext->ClearRenderTargetView(framebuffer->GetColorTextureView().Get(), frameColor);
	mDeferredContext->ClearDepthStencilView(framebuffer->GetDepthTextureView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void CommandList::UpdateDynamicBuffer(std::shared_ptr<GraphicsBuffer> buffer, void* data, uint32 size)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	mDeferredContext->Map(buffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, data, size);
	mDeferredContext->Unmap(buffer->GetBuffer().Get(), 0);
}
