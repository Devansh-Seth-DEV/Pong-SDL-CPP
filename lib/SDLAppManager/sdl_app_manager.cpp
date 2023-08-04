#include "sdl_app_manager.h"

bool SDLApp::s_initialized = false;

SDLApp::SDLApp(const char* title, const int x, const int y, const int w, const int h, Uint32 winFlags=SDL_WINDOW_SHOWN, int renderIndex=-1, Uint32 renderFlags=SDL_RENDERER_ACCELERATED)
	: m_maxFrameRate(static_cast<uint8_t>(1000/60))
{
	if(!s_initialized && SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << SDL_GetError() << std::endl;
	} else {
		std::cout << "SDL Video System Initialized" << std::endl;
		s_initialized = true;
	}

	m_window = SDL_CreateWindow(title, x, y, w, h, winFlags);
	if(m_window == nullptr) {
		std::cerr << "window initialization error: " << SDL_GetError() << std::endl;
	}

	m_renderer = SDL_CreateRenderer(m_window, renderIndex, renderFlags); 
	if(m_renderer == nullptr) {
		std::cerr << "renderer initialization error: " << SDL_GetError() << std::endl;
	}
}

SDLApp::~SDLApp() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void SDLApp::SetWindowBackgroundColor(RGB_ColorChannel color) {
	m_winBackgroundColor = color;
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

SDL_Renderer& SDLApp::GetRenderer() const {
	return *m_renderer;
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

		m_eventCallback();

		m_updateCallback();

		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(m_renderer);

		SDL_SetRenderDrawColor
		(	
			m_renderer,
			m_winBackgroundColor.red,
			m_winBackgroundColor.green,
			m_winBackgroundColor.blue,
			SDL_ALPHA_OPAQUE
		);

		m_renderCallback();

		SDL_RenderPresent(m_renderer);
	}
}

void SDLApp::StopAppLoop() {
	m_run = false;
}
