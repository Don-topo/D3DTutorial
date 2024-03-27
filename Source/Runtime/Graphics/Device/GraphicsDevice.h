#pragma once

#include <Runtime/Graphics/Device/GraphicsDeviceDesc.h>

#include <memory>
#include <vector>

#include "wrl.h"
#include "d3d11.h"
#include "d3dcompiler.h"
#include "DirectXMath.h"

using namespace Microsoft::WRL;
using namespace DirectX;

class GraphicsDeviceObject;
class Swapchain;
class Framebuffer;
class FramebufferView;
class Texture;
class TextureView;
class Shader;
class Pipeline;
class Sampler;
class CommandList;
class GraphicsBuffer;

struct SwapchainDesc;
struct FramebufferDesc;
struct FramebufferViewDesc;
struct TextureDesc;
struct TextureViewDesc;
struct ShaderDesc;
struct PipelineDesc;
struct SamplerDesc;
struct CommandListDesc;
struct GraphicsBufferDesc;

class RUNTIME_API GraphicsDevice : std::enable_shared_from_this<GraphicsDevice>
{
public:
	GraphicsDevice(const GraphicsDeviceDesc& desc);
	GraphicsDevice(const GraphicsDevice&) = delete;
	GraphicsDevice& operator=(const GraphicsDevice&) = delete;
	virtual ~GraphicsDevice() = default;

private:
	std::vector<std::shared_ptr<GraphicsDeviceObject>> mDeviceObjects;
	std::shared_ptr<Swapchain> mSwapChain;

	ComPtr<ID3D11Device> mD3D11Device;
	ComPtr<ID3D11DeviceContext> mD3D11ImmediateContext;
};