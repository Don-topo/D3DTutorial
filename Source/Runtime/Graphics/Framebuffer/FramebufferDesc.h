#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Texture/TextureFormat.h>

#include <d3d11.h>
#include <dxgi.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;


struct FramebufferDesc
{
	TextureFormat ColorAttachmentFormat;

	ComPtr<ID3D11Texture2D> ColorTexture;
	
};