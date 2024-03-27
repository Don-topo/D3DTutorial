cmake_minimum_required (VERSION 3.26)

include(FetchContent)

# GLFW LIBRARY
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.9
)

# STBI LIBRARY
FetchContent_Declare(
	stbi
	GIT_REPOSITORY https://github.com/nothings/stb.git
)