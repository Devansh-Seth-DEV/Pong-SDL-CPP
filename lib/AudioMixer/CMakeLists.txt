include_directories(${CMAKE_SYSTEM_INCLUDE_PATH}/../SDL2)
link_libraries(
	SDL2
	SDL2_mixer
)

add_library(AudioMixer audio_mixer.cpp)
