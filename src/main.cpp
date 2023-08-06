#include <iostream>

#include <SDL.h>

#include <sdl_app_manager.h>
#include <audio_mixer.h>
#include <TEX_font.h>
#include <game_entity.h>

SDLApp* app;

void EventLoop() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			app->StopAppLoop();
		}
	}
}

int main() {
	app = new SDLApp("SDL Window", 100, 100, 640, 400, SDL_WINDOW_SHOWN, -1, SDL_RENDERER_ACCELERATED);
	app->SetWindowBackgroundColor({255, 255, 255, SDL_ALPHA_OPAQUE});
	app->SetMaxFrameRate(60);

	app->SetEventCallback(EventLoop);
	app->StartAppLoop();
	return 0;
}
