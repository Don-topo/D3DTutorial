#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Texture/Texture.h>
#include <Runtime/Graphics/Texture/TextureView.h>


#include <memory>

class TextureResource
{
public:
	TextureResource() = default;
	TextureResource(const TextureResource&) = delete;
	TextureResource& operator=(const TextureResource&) = delete;
	~TextureResource() = default;

	void AllocateTexture();

	std::shared_ptr<Texture>& GetTexture() { return mTexture; }
	std::shared_ptr<TextureView>& GetTextureView() { return mTextureView; }

	uint32& GetWidth() noexcept { return mWith; }
	uint32& GetHeight() noexcept { return mHeight; }
	uint32& GetChannels() noexcept { return mCHannels; }
	uint8** GetPixelData() noexcept { return &mPixelData; }

	void SetTexture(byte* data, uint32 width, uint32 height, uint32 channels)
	{
		mPixelData = data; mWith = width; mHeight = height; mCHannels = channels;
	}

private:
	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<TextureView> mTextureView;

	uint32 mWith;
	uint32 mHeight;
	uint32 mCHannels;

	uint8* mPixelData;
};