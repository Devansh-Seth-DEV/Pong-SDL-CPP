#include <iostream>

//custom static libraries
#include <engine.h>
#include <TEX_font.h>
#include <game_entity.h>
#include <audio_mixer.h>

SDLApp app;

Entity* leftPaddle;
Entity* rightPaddle;
Entity* ball;

Mixer* collisionSound;
Mixer* scoreSound;

void FreeSprites() {
	delete leftPaddle;
	delete rightPaddle;
	delete ball;
}

void FreeSounds() {
	delete collisionSound;
	delete scoreSound;
}

void InitSprites() {
	leftPaddle = new Entity(app.GetRenderer());
	leftPaddle->AddSprite("./assets/images/pong/paddle-green.bmp");
	leftPaddle->AddCollider2D();
	
	rightPaddle = new Entity(app.GetRenderer());
	rightPaddle->AddSprite("./assets/images/pong/paddle-green.bmp");
	rightPaddle->AddCollider2D();

	ball = new Entity(app.GetRenderer());
	ball->AddSprite("./assets/images/pong/ball.bmp");
	ball->AddCollider2D();
}

void InitSounds() {
	collisionSound = new Mixer("./assets/sounds/collision.wav");
	collisionSound->SetupDevice();

	scoreSound = new Mixer("./assets/sounds/score.wav");
	scoreSound->SetupDevice();
}

void HandleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			app.StopAppLoop();
		}
	}
}

int main() {
	const char* title = "PONG";
	app.App(title, 20, 20, 640, 480, SDL_WINDOW_SHOWN, SDL_INIT_VIDEO | SDL_INIT_AUDIO, -1, SDL_RENDERER_ACCELERATED);

	InitSprites();
	InitSounds();
	app.SetEventCallback(HandleEvents);

	app.StartAppLoop();

	FreeSprites();
	FreeSounds();
	std::cout << "PROGRAM TERMINATION SUCCESSFULLY" << std::endl;
	return 0;
}
