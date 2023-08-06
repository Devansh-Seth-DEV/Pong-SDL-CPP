include_directories(${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	${CMAKE_SOURCE_DIR}/lib/ResourceManager
)

link_libraries(
	SDL2_ttf
	ResourceManager
)

add_library(texturedFont TEX_font.cpp)
