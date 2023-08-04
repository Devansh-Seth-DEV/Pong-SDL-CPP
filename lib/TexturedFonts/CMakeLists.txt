include_directories(${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	${CMAKE_SOURCE_DIR}/lib/ResourceManager
)

add_library(texturedFont TEX_font.cpp)
