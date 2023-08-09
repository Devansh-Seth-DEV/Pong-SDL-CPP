#ifndef SDL_APP_MANAGER_H
#define SDL_APP_MANAGER_H

#include <iostream>
#include <cstdint>

#include <SDL.h>

#include <manager.h>


class SDLApp {
public:
	SDLApp();
	SDLApp(const char* title, const int x, const int y, const int w, const int h, Uint32 winFlags, Uint32 winInitFlags, int renderIndex, Uint32 renderFlags);
	void App(const char* title, const int x, const int y, const int w, const int h, Uint32 winFlags, Uint32 winInitFlags, int renderIndex, Uint32 renderFlags);
	
	~SDLApp();

	void SetWindowBackgroundColor(SDL_Color color);
	void SetEventCallback(void (*func)(void));
	void SetRenderCallback(void (*func)(void));
	void SetUpdateCallback(void (*func)(void));
	void SetMaxFrameRate(uint8_t fps);

	SDL_Renderer* GetRenderer() const;
	int GetWidth() const;
	int GetHeight() const;

	void StartAppLoop();
	void StopAppLoop();

private:
	static bool s_initialized;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Color m_bgColor;
	bool m_run;
	uint8_t m_maxFrameRate;

	void (*m_renderCallback)(void);
	void (*m_updateCallback)(void);
	void (*m_eventCallback)(void);
};

#endif /* sdl_app_manager.h */
