include_directories(${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	${CMAKE_SOURCE_DIR}/lib/ResourceManager
)

link_libraries(
	ResourceManager
)

add_library(textured_rect TEX_rect.cpp)
