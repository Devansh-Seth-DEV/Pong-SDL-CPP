include_directories(
	${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2 
)

link_libraries(
	SDL2
	SDL2_ttf
)

add_library(ResourceManager manager.cpp)
