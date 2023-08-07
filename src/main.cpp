#include <iostream>

#include <SDL.h>

#include <engine.h>
#include <audio_mixer.h>
#include <TEX_font.h>
#include <game_entity.h>

SDLApp app;
TexturedFont label;

void HandleEvent() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			app.StopAppLoop();
		}
	}
}


void HandleRender() {
	label.Render();
}

int main() {
	const char* fontPath = "./assets/fonts/Open_24_Display_St.ttf";
	const char* text = "HELLO WORLD";
	SDL_Color textfg = {255, 255, 255, SDL_ALPHA_OPAQUE};
	SDL_Renderer* renderer;

	app.App("SDL Greeting", 100, 100, 640, 400, SDL_WINDOW_SHOWN, -1, SDL_RENDERER_ACCELERATED); 
	app.SetWindowBackgroundColor({0, 0, 0, SDL_ALPHA_OPAQUE});
	app.SetMaxFrameRate(60);
	renderer = app.GetRenderer();
	
	label.Label(renderer, fontPath, 32, text, textfg);
	label.SetRect(app.GetWidth()/2-150, app.GetHeight()/2-50-32, 300, 100);

	app.SetEventCallback(HandleEvent);
	app.SetRenderCallback(HandleRender);
	app.StartAppLoop();
	return 0;
}
