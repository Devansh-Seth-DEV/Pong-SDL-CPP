include_directories(${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	${CMAKE_SOURCE_DIR}/lib/ResourceManager
)

link_libraries(
	SDL2
	ResourceManager
)

add_library(SDLEngine engine.cpp)
