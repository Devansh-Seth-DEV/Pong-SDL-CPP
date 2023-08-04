include_directories(${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	${CMAKE_SOURCE_DIR}/include
)

add_library(appManager sdl_app_manager.cpp)
