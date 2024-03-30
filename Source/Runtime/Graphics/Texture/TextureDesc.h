#pragma once

#include <Runtime/Core/Core.h>
#include <DirectXMath.h>
#include <Runtime/Graphics/Texture/TextureFormat.h>

using namespace DirectX;

struct TextureDesc
{
	XMUINT3 TextureSize;
	uint32 MipLevels;
	uint32 ArraySize;
	TextureFormat Format;
	uint32 SampleCount;
	uint32 SampleQuality;

	void* InitialData;
};