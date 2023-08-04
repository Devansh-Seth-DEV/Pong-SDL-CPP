#include "audio_mixer.h"

Mixer::Mixer(const char* filepath) {
	SDL_AudioSpec* audioSpec = SDL_LoadWAV(filepath, &m_spec, &m_audioBuff, &m_audioLen);
	if(audioSpec == nullptr) {
		std::cerr << "mixer loading error: " << SDL_GetError() << std::endl;
	} else {
		std::cout << "mixer loaded: " << filepath << std::endl;
	}
};

Mixer::~Mixer() {
	SDL_FreeWAV(m_audioBuff);
	SDL_CloseAudioDevice(m_dev);
}

void Mixer::PlaySound() {
	int status = SDL_QueueAudio(m_dev, m_audioBuff, m_audioLen);
	if(status < 0) {
		std::cerr << "mixer play error: " << SDL_GetError() << std::endl;
	}
	SDL_PauseAudioDevice(m_dev, status);
}

void Mixer::StopSound() {
	SDL_PauseAudioDevice(m_dev, 1);
}

void Mixer::SetupDevice() {
	m_dev = SDL_OpenAudioDevice(nullptr, 0, &m_spec, nullptr, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
	if(m_dev == 0) {
		std::cerr << "mixer device error: " << SDL_GetError() << std::endl;
	}
}
