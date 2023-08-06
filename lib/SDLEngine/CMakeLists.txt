include_directories(${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	${CMAKE_SOURCE_DIR}/include
)

add_library(SDLEngine engine.cpp)
