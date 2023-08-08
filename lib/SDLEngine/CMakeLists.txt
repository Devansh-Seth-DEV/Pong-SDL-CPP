include_directories(${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	${CMAKE_SOURCE_DIR}/include
)

link_libraries(SDL2)

add_library(SDLEngine engine.cpp)
