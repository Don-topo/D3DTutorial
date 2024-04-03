cmake_minimum_required (VERSION 3.26)

# INCLUDE 3RD PARTY LIBRARIES
include("${CMAKE_SOURCE_DIR}/Scripts/FetchLibraries.cmake")

# POPULATE 3RD PARTY LIBRARIES
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(stbi)
FetchContent_MakeAvailable(assimp)

# CREATE EXECUTABLE
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Source/Runtime/*.h" "${CMAKE_SOURCE_DIR}/Source/Runtime/*.cpp")
source_group("Runtime" "${CMAKE_SOURCE_DIR}/Source/Runtime" ${SUBDIRECTORIES})
add_library ("Runtime" STATIC main.cpp ${SUBDIRECTORIES} "Window/Window.h" "Window/Window.cpp" "Core/Core.h" "Core/Core.cpp" "Graphics/Device/GraphicsDevice.cpp" "Graphics/Swapchain/Swapchain.h" "Graphics/Swapchain/Swapchain.cpp" "Graphics/Framebuffer/Framebuffer.h" "Graphics/Framebuffer/Framebuffer.cpp"   "Graphics/Framebuffer/FramebufferDesc.h"   "Graphics/Swapchain/SwapchainDesc.h" "Graphics/Texture/TextureFormat.h" "Graphics/Texture/TextureUtils.h" "Graphics/Texture/Texture.h" "Graphics/Texture/TextureDesc.h" "Graphics/Texture/Texture.cpp" "Graphics/Texture/TextureView.h" "Graphics/Texture/TextureView.cpp" "Graphics/Texture/ShaderResourceViewDimension.h" "Graphics/Texture/TextureViewDesc.h" "Graphics/Buffer/GraphicsBuffer.h" "Graphics/Buffer/GraphicsBuffer.cpp" "Graphics/Buffer/GraphicsBufferDesc.h" "Graphics/Buffer/BufferUtils.h" "Graphics/Buffer/BufferUsage.h" "Graphics/Buffer/BufferCPUAccess.h" "Graphics/Buffer/BufferResourceUsage.h" "Graphics/Shader/Shader.h" "Graphics/Shader/Shader.cpp" "Graphics/Shader/ShaderDesc.h" "Graphics/Shader/ShaderType.h" "Graphics/Shader/ShaderReader.h" "Core/PlatformDirectory.h" "Graphics/Shader/ShaderStage.h" "Graphics/Pipeline/Pipeline.h" "Graphics/Pipeline/Pipeline.cpp" "Graphics/Pipeline/PipelineDesc.h" "Graphics/Pipeline/Blend/BlendOperation.h" "Graphics/Pipeline/Blend/ColorMask.h" "Graphics/Pipeline/Blend/BlendType.h" "Graphics/Pipeline/Blend/BlendStateDesc.h" "Graphics/Pipeline/Blend/RenderTargetBlendDesc.h" "Graphics/Pipeline/PipelineUtils.h" "Graphics/Pipeline/DepthStencil/DepthMask.h" "Graphics/Pipeline/DepthStencil/DepthStencilComparisonFunc.h" "Graphics/Pipeline/DepthStencil/DepthStencilDesc.h" "Graphics/Pipeline/InputLayout/SemanticName.h" "Graphics/Pipeline/InputLayout/SlotClass.h" "Graphics/Pipeline/InputLayout/PrimitiveMode.h" "Graphics/Pipeline/InputLayout/InputLayoutDesc.h"  "Graphics/Pipeline/Rasterizer/FillMode.h" "Graphics/Pipeline/Rasterizer/CullMode.h" "Graphics/Pipeline/Rasterizer/FaceOrdering.h" "Graphics/Pipeline/Rasterizer/RasterizerDesc.h" "Graphics/Sampler/Sampler.h" "Graphics/Sampler/Sampler.cpp" "Graphics/Sampler/SamplerDesc.h" "Graphics/Sampler/SamplerFilter.h" "Graphics/Sampler/AddressMode.h" "Graphics/Sampler/SamplerComparison.h" "Graphics/Sampler/SamplerUtils.h" "Graphics/Command/CommandList.h" "Graphics/Command/CommandList.cpp" "Resources/ResourceImporter.h" "Resources/ResourceImporter.cpp" "Resources/Mesh/Mesh.h" "Resources/Mesh/Mesh.cpp"  "Resources/Texture/TextureResource.h" "Resources/Texture/TextureResource.cpp" "Containers/Singleton.h" "Graphics/GraphicsManager.h" "Application/Application.h" "Application/Application.cpp" "Window/WindowManager.h" "Application/ApplicationManager.h" "World/ObjectPipeline.h" "World/ObjectPipeline.cpp")

# INCLUDE DIRECTORIES AND LINK LIBRARIES
target_include_directories("Runtime" PRIVATE "${CMAKE_SOURCE_DIR}/Source")

# LINK STBI
if (stbi_POPULATED) 
    target_compile_definitions(Runtime PUBLIC STB_IMAGE_IMPLEMENTATION=1)
    target_include_directories(Runtime PUBLIC ${stbi_SOURCE_DIR})
else ()
    target_compile_definitions(Runtime PUBLIC STB_IMAGE_IMPLEMENTATION=0)
endif ()

target_link_libraries("Runtime" PUBLIC glfw)
target_link_libraries("Runtime" PUBLIC assimp)
target_link_libraries("Runtime" PUBLIC d3d11.lib)
target_link_libraries("Runtime" PUBLIC dxgi.lib)
target_link_libraries("Runtime" PUBLIC d3dcompiler.lib)
target_link_libraries("Runtime" PUBLIC dxguid.lib)

# DEBUG AND RELEASE FLAGS
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions("Runtime" PUBLIC TUTORIAL_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_definitions("Runtime" PUBLIC TUTORIAL_RELEASE)
endif()

# MACRO DEFINITIONS
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_definitions("Runtime" PUBLIC RUNTIME_API=__declspec\(dllexport\))
	target_compile_definitions("Runtime" PUBLIC FORCEINLINE=__forceinline)
else()
	message(FATAL_ERROR "Unsupported Compiler")
endif()

# ROOT DIRECTORY
add_compile_definitions("SHADER_ROOT=${CMAKE_SOURCE_DIR}/Shaders/")
add_compile_definitions("WORKING_ROOT=${CMAKE_SOURCE_DIR}")