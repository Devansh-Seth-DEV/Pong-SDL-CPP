#ifndef SDL_APP_MANAGER_H
#define SDL_APP_MANAGER_H

#include <iostream>
#include <cstdint>

#include <SDL.h>

struct RGB_ColorChannel {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

class SDLApp {
public:
	SDLApp(const char* title, const int x, const int y, const int w, const int h, Uint32 winFlags, int renderIndex, Uint32 renderFlags);
	
	~SDLApp();

	void SetWindowBackgroundColor(RGB_ColorChannel color);
	void SetEventCallback(void (*func)(void));
	void SetRenderCallback(void (*func)(void));
	void SetUpdateCallback(void (*func)(void));
	void SetMaxFrameRate(uint8_t fps);

	SDL_Renderer& GetRenderer() const;
	int GetWidth() const;
	int GetHeight() const;

	void StartAppLoop();
	void StopAppLoop();

private:
	static bool s_initialized;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	RGB_ColorChannel m_winBackgroundColor;
	bool m_run;
	uint8_t m_maxFrameRate;

	void (*m_renderCallback)(void);
	void (*m_updateCallback)(void);
	void (*m_eventCallback)(void);
};

#endif /* sdl_app_manager.h */