#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Texture/TextureFormat.h>
#include <Runtime/Graphics/Texture/ShaderResourceViewDimension.h>

#include <d3d11.h>

class TextureUtils
{
public:
	static DXGI_FORMAT GetTextureFormat(TextureFormat format) noexcept
	{
		switch (format) {
		case TextureFormat::UNKNOWN:
			return DXGI_FORMAT_UNKNOWN;
		case TextureFormat::RGBA32_TYPELESS:
			return DXGI_FORMAT_R32G32B32A32_TYPELESS;
		case TextureFormat::RGBA32_FLOAT:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case TextureFormat::RGBA32_UNSIGNED_INT:
			return DXGI_FORMAT_R32G32B32A32_UINT;
		case TextureFormat::RGBA32_SIGNED_INT:
			return DXGI_FORMAT_R32G32B32A32_SINT;
		case TextureFormat::RGB32_TYPELESS:
			return DXGI_FORMAT_R32G32B32_TYPELESS;
		case TextureFormat::RGB32_FLOAT:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case TextureFormat::RGB32_UNSIGNED_INT:
			return DXGI_FORMAT_R32G32B32_UINT;
		case TextureFormat::RGB32_SIGNED_INT:
			return DXGI_FORMAT_R32G32B32_SINT;
		case TextureFormat::RGBA16_TYPELESS:
			return DXGI_FORMAT_R16G16B16A16_TYPELESS;
		case TextureFormat::RGBA16_FLOAT:
			return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case TextureFormat::RGBA16_UNSIGNED_NORMALIZED:
			return DXGI_FORMAT_R16G16B16A16_UNORM;
		case TextureFormat::RGBA16_UNSIGNED_INT:
			return DXGI_FORMAT_R16G16B16A16_UINT;
		case TextureFormat::RGBA16_SIGNED_NORMALIZED:
			return DXGI_FORMAT_R16G16B16A16_SNORM;
		case TextureFormat::RGBA16_SIGNED_INT:
			return DXGI_FORMAT_R16G16B16A16_SINT;
		case TextureFormat::RG32_TYPELESS:
			return DXGI_FORMAT_R32G32_TYPELESS;
		case TextureFormat::RG32_FLOAT:
			return DXGI_FORMAT_R32G32_FLOAT;
		case TextureFormat::RG32_UNSIGNED_INT:
			return DXGI_FORMAT_R32G32_UINT;
		case TextureFormat::RG32_SIGNED_INT:
			return DXGI_FORMAT_R32G32_SINT;
		case TextureFormat::RGBA8_TYPELESS:
			return DXGI_FORMAT_R8G8B8A8_TYPELESS;
		case TextureFormat::RGBA8_UNSIGNED_NORMALIZED:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case TextureFormat::RGBA8_UNSIGNED_INT:
			return DXGI_FORMAT_R8G8B8A8_UINT;
		case TextureFormat::RGBA8_SIGNED_NORMALIZED:
			return DXGI_FORMAT_R8G8B8A8_SNORM;
		case TextureFormat::RGBA8_SIGNED_INT:
			return DXGI_FORMAT_R8G8B8A8_SINT;
		case TextureFormat::RG16_TYPELESS:
			return DXGI_FORMAT_R16G16_TYPELESS;
		case TextureFormat::RG16_FLOAT:
			return DXGI_FORMAT_R16G16_FLOAT;
		case TextureFormat::RG16_UNSIGNED_NORMALIZED:
			return DXGI_FORMAT_R16G16_UNORM;
		case TextureFormat::RG16_UNSIGNED_INT:
			return DXGI_FORMAT_R16G16_UINT;
		case TextureFormat::RG16_SIGNED_NORMALIZED:
			return DXGI_FORMAT_R16G16_SNORM;
		case TextureFormat::RG16_SIGNED_INT:
			return DXGI_FORMAT_R16G16_SINT;
		case TextureFormat::R32_TYPELESS:
			return DXGI_FORMAT_R32_TYPELESS;
		case TextureFormat::D32_FLOAT:
			return DXGI_FORMAT_D32_FLOAT;
		case TextureFormat::R32_FLOAT:
			return DXGI_FORMAT_R32_FLOAT;
		case TextureFormat::R32_UNSIGNED_INT:
			return DXGI_FORMAT_R32_UINT;
		case TextureFormat::R32_SIGNED_INT:
			return DXGI_FORMAT_R32_SINT;
		case TextureFormat::D24_UNSIGNED_NORMALIZED_S8_UNSIGNED_INT:
			return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case TextureFormat::R24_UNSIGNED_NORMALIZED_X8_TYPELESS:
			return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case TextureFormat::RG8_TYPELESS:
			return DXGI_FORMAT_R8G8_TYPELESS;
		case TextureFormat::RG8_UNSIGNED_NORMALIZED:
			return DXGI_FORMAT_R8G8_UNORM;
		case TextureFormat::RG8_UNSIGNED_INT:
			return DXGI_FORMAT_R8G8_UINT;
		case TextureFormat::RG8_SIGNED_NORMALIZED:
			return DXGI_FORMAT_R8G8_SNORM;
		case TextureFormat::RG8_SIGNED_INT:
			return DXGI_FORMAT_R8G8_SINT;
		case TextureFormat::R16_TYPELESS:
			return DXGI_FORMAT_R16_TYPELESS;
		case TextureFormat::R16_FLOAT:
			return DXGI_FORMAT_R16_FLOAT;
		case TextureFormat::D16_UNSIGNED_NORMALIZED:
			return DXGI_FORMAT_D16_UNORM;
		case TextureFormat::R16_UNSIGNED_NORMALIZED:
			return DXGI_FORMAT_R16_UNORM;
		case TextureFormat::R16_UNSIGNED_INT:
			return DXGI_FORMAT_R16_UINT;
		case TextureFormat::R16_SIGNED_NORMALIZED:
			return DXGI_FORMAT_R16_SNORM;
		case TextureFormat::R16_SIGNED_INT:
			return DXGI_FORMAT_R16_SINT;
		case TextureFormat::R8_TYPELESS:
			return DXGI_FORMAT_R8_TYPELESS;
		case TextureFormat::R8_UNSIGNED_NORMALIZED:
			return DXGI_FORMAT_R8_UNORM;
		case TextureFormat::R8_UNSIGNED_INT:
			return DXGI_FORMAT_R8_UINT;
		case TextureFormat::R8_SIGNED_NORMALIZED:
			return DXGI_FORMAT_R8_SNORM;
		case TextureFormat::R8_SIGNED_INT:
			return DXGI_FORMAT_R8_SINT;
		case TextureFormat::A8_UNSIGNED_NORMALIZED:
			return DXGI_FORMAT_A8_UNORM;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	static D3D11_SRV_DIMENSION GetSRVDimension(ShaderResourceViewDimension srvDimension) 
	{
		switch (srvDimension) {
		case ShaderResourceViewDimension::UNKNOWN:
			return D3D11_SRV_DIMENSION_UNKNOWN;
		case ShaderResourceViewDimension::BUFFER:
			return D3D11_SRV_DIMENSION_BUFFER;
		case ShaderResourceViewDimension::TEXTURE1D:
			return D3D11_SRV_DIMENSION_TEXTURE1D;
		case ShaderResourceViewDimension::TEXTURE1D_ARRAY:
			return D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
		case ShaderResourceViewDimension::TEXTURE2D:
			return D3D11_SRV_DIMENSION_TEXTURE2D;
		case ShaderResourceViewDimension::TEXTURE2D_ARRAY:
			return D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		case ShaderResourceViewDimension::TEXTURE2D_MS:
			return D3D11_SRV_DIMENSION_TEXTURE2DMS;
		case ShaderResourceViewDimension::TEXTURE2D_MS_ARRAY:
			return D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
		case ShaderResourceViewDimension::TEXTURE3D:
			return D3D11_SRV_DIMENSION_TEXTURE3D;
		case ShaderResourceViewDimension::TEXTURE_CUBE:
			return D3D11_SRV_DIMENSION_TEXTURECUBE;
		case ShaderResourceViewDimension::TEXTURE_CUBE_ARRAY:
			return D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
		default:
			return D3D11_SRV_DIMENSION_UNKNOWN;
		}
	}

	static uint32 GetTextureFormatSize(TextureFormat format)
	{
		switch (format) {
		case TextureFormat::UNKNOWN:
			return 0;
		case TextureFormat::RGBA32_TYPELESS:
			return 16;
		case TextureFormat::RGBA32_FLOAT:
			return 16;
		case TextureFormat::RGBA32_UNSIGNED_INT:
			return 16;
		case TextureFormat::RGBA32_SIGNED_INT:
			return 16;
		case TextureFormat::RGB32_TYPELESS:
			return 12;
		case TextureFormat::RGB32_FLOAT:
			return 12;
		case TextureFormat::RGB32_UNSIGNED_INT:
			return 12;
		case TextureFormat::RGB32_SIGNED_INT:
			return 12;
		case TextureFormat::RGBA16_TYPELESS:
			return 8;
		case TextureFormat::RGBA16_FLOAT:
			return 8;
		case TextureFormat::RGBA16_UNSIGNED_NORMALIZED:
			return 8;
		case TextureFormat::RGBA16_UNSIGNED_INT:
			return 8;
		case TextureFormat::RGBA16_SIGNED_NORMALIZED:
			return 8;
		case TextureFormat::RGBA16_SIGNED_INT:
			return 8;
		case TextureFormat::RG32_TYPELESS:
			return 8;
		case TextureFormat::RG32_FLOAT:
			return 8;
		case TextureFormat::RG32_UNSIGNED_INT:
			return 8;
		case TextureFormat::RG32_SIGNED_INT:
			return 8;
		case TextureFormat::RGBA8_TYPELESS:
			return 4;
		case TextureFormat::RGBA8_UNSIGNED_NORMALIZED:
			return 4;
		case TextureFormat::RGBA8_UNSIGNED_INT:
			return 4;
		case TextureFormat::RGBA8_SIGNED_NORMALIZED:
			return 4;
		case TextureFormat::RGBA8_SIGNED_INT:
			return 4;
		case TextureFormat::RG16_TYPELESS:
			return 4;
		case TextureFormat::RG16_FLOAT:
			return 4;
		case TextureFormat::RG16_UNSIGNED_NORMALIZED:
			return 4;
		case TextureFormat::RG16_UNSIGNED_INT:
			return 4;
		case TextureFormat::RG16_SIGNED_NORMALIZED:
			return 4;
		case TextureFormat::RG16_SIGNED_INT:
			return 4;
		case TextureFormat::R32_TYPELESS:
			return 4;
		case TextureFormat::D32_FLOAT:
			return 4;
		case TextureFormat::R32_FLOAT:
			return 4;
		case TextureFormat::R32_UNSIGNED_INT:
			return 4;
		case TextureFormat::R32_SIGNED_INT:
			return 4;
		case TextureFormat::D24_UNSIGNED_NORMALIZED_S8_UNSIGNED_INT:
			return 4;
		case TextureFormat::R24_UNSIGNED_NORMALIZED_X8_TYPELESS:
			return 4;
		case TextureFormat::RG8_TYPELESS:
			return 2;
		case TextureFormat::RG8_UNSIGNED_NORMALIZED:
			return 2;
		case TextureFormat::RG8_UNSIGNED_INT:
			return 2;
		case TextureFormat::RG8_SIGNED_NORMALIZED:
			return 2;
		case TextureFormat::RG8_SIGNED_INT:
			return 2;
		case TextureFormat::R16_TYPELESS:
			return 2;
		case TextureFormat::R16_FLOAT:
			return 2;
		case TextureFormat::D16_UNSIGNED_NORMALIZED:
			return 2;
		case TextureFormat::R16_UNSIGNED_NORMALIZED:
			return 2;
		case TextureFormat::R16_UNSIGNED_INT:
			return 2;
		case TextureFormat::R16_SIGNED_NORMALIZED:
			return 2;
		case TextureFormat::R16_SIGNED_INT:
			return 2;
		case TextureFormat::R8_TYPELESS:
			return 1;
		case TextureFormat::R8_UNSIGNED_NORMALIZED:
			return 1;
		case TextureFormat::R8_UNSIGNED_INT:
			return 1;
		case TextureFormat::R8_SIGNED_NORMALIZED:
			return 1;
		case TextureFormat::R8_SIGNED_INT:
			return 1;
		case TextureFormat::A8_UNSIGNED_NORMALIZED:
			return 1;
		default:
			return 0;
		}
	}


private:

};