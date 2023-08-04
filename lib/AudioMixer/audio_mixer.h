#ifndef AUDIO_MIXER_H
#define AUDIO_MIXER_H

#include <SDL.h>
#include <iostream>

class Mixer {
public:
	Mixer(const char* filepath);
	~Mixer();

	void PlaySound();
	void StopSound();
	void SetupDevice();

private:
	SDL_AudioDeviceID m_dev;
	SDL_AudioSpec m_spec;
	Uint8* m_audioBuff;
	Uint32 m_audioLen;
};

#endif /* audio_mixer.h */
