#include "engine.h"

bool SDLApp::s_initialized = false;

SDLApp::SDLApp()
	: m_maxFrameRate(static_cast<uint8_t>(1000/60)), m_renderCallback(nullptr), m_updateCallback(nullptr), m_eventCallback(nullptr)
{}

SDLApp::SDLApp(const char* title, const int x, const int y, const int w, const int h, Uint32 winFlags, Uint32 winInitFlags, int renderIndex, Uint32 renderFlags)
	: m_maxFrameRate(static_cast<uint8_t>(1000/60)), m_renderCallback(nullptr), m_updateCallback(nullptr), m_eventCallback(nullptr)
{
	App(title, x, y, w, h, winFlags, winInitFlags, renderIndex, renderFlags);
}

void SDLApp::App(const char* title, const int x, const int y, const int w, const int h, Uint32 winFlags, Uint32 winInitFlags, int renderIndex, Uint32 renderFlags) {
	if(!s_initialized && SDL_Init(winInitFlags) < 0) {
		std::cerr << SDL_GetError() << std::endl;
	} else {
		std::cout << "SDL subSystem initialized" << std::endl;
		s_initialized = true;
	}

	m_window = SDL_CreateWindow(title, x, y, w, h, winFlags);
	if(m_window == nullptr) {
		std::cerr << "window initialization error: " << SDL_GetError() << std::endl;
	} else {
		std::cout << "window initialized" << std::endl;
	}

	m_renderer = SDL_CreateRenderer(m_window, renderIndex, renderFlags); 
	if(m_renderer == nullptr) {
		std::cerr << "renderer initialization error: " << SDL_GetError() << std::endl;
	} else {
		std::cout << "renderer initialized" << std::endl;
	}
}

SDLApp::~SDLApp() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void SDLApp::SetWindowBackgroundColor(SDL_Color color) {
	m_bgColor = color;
}

void SDLApp::SetEventCallback(void (*func)(void)) {
	m_eventCallback = func;
}

void SDLApp::SetRenderCallback(void (*func)(void)) {
	m_renderCallback = func;
}

void SDLApp::SetUpdateCallback(void (*func)(void)) {
	m_updateCallback = func;
}

void SDLApp::SetMaxFrameRate(uint8_t fps) {
	m_maxFrameRate = static_cast<uint8_t>(1000/fps);
}

SDL_Renderer* SDLApp::GetRenderer() const {
	return m_renderer;
}

int SDLApp::GetWidth() const {
	int w;
	SDL_GetWindowSize(m_window, &w, nullptr);
	return w;
}

int SDLApp::GetHeight() const {
	int h;
	SDL_GetWindowSize(m_window, nullptr, &h);
	return h;
}

void SDLApp::StartAppLoop() {
	m_run = true;
	while(m_run) {
		Uint32 startTicks = SDL_GetTicks();

		if(m_eventCallback != nullptr) {
			m_eventCallback();
		}

		if(m_updateCallback != nullptr) {
			m_updateCallback();
		}
		//SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		//SDL_RenderClear(m_renderer);

		SDL_SetRenderDrawColor(	
			m_renderer,
			m_bgColor.r,
			m_bgColor.g,
			m_bgColor.b,
			m_bgColor.a
		);
		SDL_RenderClear(m_renderer);

		if(m_renderCallback != nullptr) {
			m_renderCallback();
		}

		SDL_RenderPresent(m_renderer);

		Uint32 elapsedTime = SDL_GetTicks() - startTicks;
		if(elapsedTime < m_maxFrameRate) {
			SDL_Delay(m_maxFrameRate - elapsedTime);
		}
	}
}

void SDLApp::StopAppLoop() {
	m_run = false;
}
