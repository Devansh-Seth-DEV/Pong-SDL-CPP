include_directories(
	${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	${CMAKE_SOURCE_DIR}/lib/TexturedRectangle
	${CMAKE_SOURCE_DIR}/lib/Collider2D
)

add_library(GameEntity game_entity.cpp)
