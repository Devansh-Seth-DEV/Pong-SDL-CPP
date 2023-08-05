cmake_minimum_required(VERSION 3.2)

project(SDL_PRACTICE VERSION 1.0)

file(GLOB SourceFiles CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SourceFiles})

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/ResourceManager)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/SDLAppManager)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/TexturedRectangle)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/AudioMixer)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/TexturedFonts)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Collider2D)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/GameEntity)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2
	PUBLIC ${PROJECT_BINARY_DIR}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/lib/ResourceManager
	PUBLIC ${PROJECT_SOURCE_DIR}/lib/SDLAppManager
	PUBLIC ${PROJECT_SOURCE_DIR}/lib/TexturedRectangle
	PUBLIC ${PROJECT_SOURCE_DIR}/lib/AudioMixer
	PUBLIC ${PROJECT_SOURCE_DIR}/lib/TexturedFonts
	PUBLIC ${PROJECT_SOURCE_DIR}/lib/Collider2D
	PUBLIC ${PROJECT_SOURCE_DIR}/lib/GameEntity
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE SDL2
	PRIVATE dl
	PRIVATE ResourceManager
	PRIVATE textured_rect
	PRIVATE appManager
	PRIVATE AudioMixer
	PRIVATE texturedFont
	PRIVATE Collider2D
	PRIVATE GameEntity
)
