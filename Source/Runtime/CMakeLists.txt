cmake_minimum_required (VERSION 3.26)

# INCLUDE 3RD PARTY LIBRARIES
include("${CMAKE_SOURCE_DIR}/Scripts/FetchLibraries.cmake")

# POPULATE 3RD PARTY LIBRARIES
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(stbi)

# CREATE EXECUTABLE
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Source/Runtime/*.h" "${CMAKE_SOURCE_DIR}/Source/Runtime/*.cpp")
source_group("Runtime" "${CMAKE_SOURCE_DIR}/Source/Runtime" ${SUBDIRECTORIES})
add_library ("Runtime" STATIC main.cpp ${SUBDIRECTORIES} "Window/Window.h" "Window/Window.cpp" "Core/Core.h" "Core/Core.cpp" "Graphics/Device/GraphicsDevice.cpp" "Graphics/Swapchain/Swapchain.h" "Graphics/Swapchain/Swapchain.cpp" "Graphics/Framebuffer/Framebuffer.h" "Graphics/Framebuffer/Framebuffer.cpp"   "Graphics/Framebuffer/FramebufferDesc.h"   "Graphics/Swapchain/SwapchainDesc.h" "Graphics/Texture/TextureFormat.h" "Graphics/Texture/TextureUtils.h")

# INCLUDE DIRECTORIES AND LINK LIBRARIES
target_include_directories("Runtime" PRIVATE "${CMAKE_SOURCE_DIR}/Source")

target_link_libraries("Runtime" PUBLIC glfw)
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