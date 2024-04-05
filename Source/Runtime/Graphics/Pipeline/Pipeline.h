#pragma	once

#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
/*#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Pipeline/InputLayout/InputLayoutDesc.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/RasterizerDesc.h>

#include <Runtime/Graphics/Pipeline/Blend/BlendStateDesc.h>
#include <Runtime/Graphics/Sampler/Sampler.h>*/
#include <Runtime/Graphics/Pipeline/PipelineDesc.h>

#include <vector>
#include <d3d11.h>

class Pipeline : public GraphicsDeviceObject
{
public:
	Pipeline(std::shared_ptr<GraphicsDevice> device, const PipelineDesc& desc);
	~Pipeline() override = default;

	DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::Pipeline; }

	std::vector<std::shared_ptr<Shader>>& GetShaders() noexcept { return mShaders; }
	InputLayoutDesc& GetInputLayout() noexcept { return mInputLayout; }
	RasterizerDesc& GetRasterizer() noexcept { return mRasterizer; }
	DepthStencilDesc& GetDepthStencil() noexcept { return mDepthStencil; }
	BlenderStateDesc& GetBlend() noexcept { return mBlend; }
	std::shared_ptr<Sampler>& GetSampler() noexcept { return mSampler; }

	ComPtr<ID3D11InputLayout>& GetInputLayoutObject() noexcept { return mInputLayoutObject; }
	ComPtr<ID3D11RasterizerState>& GetRasterizerObject() noexcept { return mRasterizerObject; }
	ComPtr<ID3D11DepthStencilState>& GetDepthStencilObject() noexcept { return mDepthStencilObject; }
	ComPtr<ID3D11BlendState>& GetBlendObject() noexcept { return mBlendObject; }
	ComPtr<ID3D11SamplerState>& GetSamplerObject() noexcept { return mSamplerObject; }

	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology();

	void SetPrimitiveMode(PrimitiveMode mode) { mInputLayout.PrimitiveMode = mode; }

private:
	void CreateDepthStencilState();
	void CreateRasterizerState();
	void CreateBlendState();

	std::vector<std::shared_ptr<Shader>> mShaders;
	InputLayoutDesc mInputLayout;
	RasterizerDesc mRasterizer;
	DepthStencilDesc mDepthStencil;
	BlenderStateDesc mBlend;
	std::shared_ptr<Sampler> mSampler;

	ComPtr<ID3D11InputLayout> mInputLayoutObject;
	ComPtr<ID3D11RasterizerState> mRasterizerObject;
	ComPtr<ID3D11DepthStencilState> mDepthStencilObject;
	ComPtr<ID3D11BlendState> mBlendObject;
	ComPtr<ID3D11SamplerState> mSamplerObject;

};