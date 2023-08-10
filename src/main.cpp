#include <iostream>

//custom static libraries
#include <engine.h>
#include <TEX_font.h>
#include <game_entity.h>
#include <audio_mixer.h>

#define PADDLE_SPRITE "./assets/images/pong/paddle-green.bmp"
#define BALL_SPRITE "./assets/images/pong/ball.bmp"
#define FONT_FILE "./assets/fonts/Open_24_Display_St.ttf"
#define COLLISION_SOUND "./assets/sounds/collision.wav"
#define SCORE_SOUND "./assets/sounds/score.wav"
#define FONT_SIZE 16

// global variables
SDLApp app;

Entity* leftPaddle;
Entity* rightPaddle;
Entity* ball;

Mixer* collisionSound;
Mixer* scoreSound;

TexturedFont* leftScoreLabel;
TexturedFont* rightScoreLabel;

SDL_Color fontFg = {255, 255, 255, SDL_ALPHA_OPAQUE};
int leftScore = 0;
int rightScore = 0;

void FreeSprites() {
	delete leftPaddle;
	delete rightPaddle;
	delete ball;
}

void FreeSounds() {
	delete collisionSound;
	delete scoreSound;
}

void FreeLabels() {
	delete leftScoreLabel;
	delete rightScoreLabel;
}

void IncLeftScore() {
	leftScore++;
	const char* label = std::string("LEFT " + std::to_string(leftScore)).c_str();
	leftScoreLabel->SetLabel(label);
}

void IncRightScore() {
	rightScore++;
	const char* label = std::string("RIGHT " + std::to_string(rightScore)).c_str();
	rightScoreLabel->SetLabel(label);
}

void InitSprites() {
	SDL_Rect paddle = {0, app.GetHeight()/2-(128/2), 32, 128};
	SDL_Rect ballRect = {app.GetWidth()/2, app.GetHeight()/2, 20, 20};

	leftPaddle = new Entity(app.GetRenderer());
	leftPaddle->AddSprite(PADDLE_SPRITE);
	leftPaddle->AddCollider2D();
	leftPaddle->SetRect(paddle.x, paddle.y, paddle.w, paddle.h);
	leftPaddle->SetRect(0, leftPaddle->GetRect());
	
	rightPaddle = new Entity(app.GetRenderer());
	rightPaddle->AddSprite(PADDLE_SPRITE);
	rightPaddle->SetRect(app.GetWidth()-paddle.w, paddle.y, paddle.w, paddle.h);
	rightPaddle->AddCollider2D();
	rightPaddle->SetRect(0, rightPaddle->GetRect());

	ball = new Entity(app.GetRenderer());
	ball->AddSprite(BALL_SPRITE);
	ball->AddCollider2D();
	ball->SetRect(ballRect.x-ballRect.w, ballRect.y-ballRect.h, ballRect.w, ballRect.h);
	ball->SetRect(0, ball->GetRect());
}

void InitSounds() {
	collisionSound = new Mixer(COLLISION_SOUND);
	collisionSound->SetupDevice();

	scoreSound = new Mixer(SCORE_SOUND);
	scoreSound->SetupDevice();
}

void InitScores() {
	SDL_Rect scoreRect = {leftPaddle->GetPosX()+leftPaddle->GetWidth(), 0, 70, FONT_SIZE};

	leftScoreLabel = new TexturedFont(app.GetRenderer(), FONT_FILE, FONT_SIZE, "LEFT 0", fontFg);
	leftScoreLabel->SetRect(scoreRect);
	leftScoreLabel->SetDrawRect(false);
	
	rightScoreLabel = new TexturedFont(app.GetRenderer(), FONT_FILE, FONT_SIZE, "RIGHT 0", fontFg);
	rightScoreLabel->SetRect(rightPaddle->GetPosX()-scoreRect.w-10, scoreRect.y, scoreRect.w, scoreRect.h);
	rightScoreLabel->SetDrawRect(false);
}


void HandleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			app.StopAppLoop();
		}

		if(event.type == SDL_KEYDOWN) {
			int y = leftPaddle->GetPosY();
			if(event.key.keysym.sym == SDLK_w) {
				// change left paddle position in upward direction
				IncLeftScore();
			} else if(event.key.keysym.sym == SDLK_s) {
				// change left paddle position in downward direction
			} else if(event.key.keysym.sym == SDLK_i) {
				IncRightScore();
			} else if(event.key.keysym.sym == SDLK_k) {
			}

		}	
	}
}

void HandleRenders() {
	leftScoreLabel->Render();
	rightScoreLabel->Render();

	leftPaddle->Render();
	rightPaddle->Render();
	ball->Render();
}

int main() {
	const char* title = "PONG";
	app.App(title, 20, 20, 640, 480, SDL_WINDOW_SHOWN, SDL_INIT_VIDEO | SDL_INIT_AUDIO, -1, SDL_RENDERER_ACCELERATED);

	InitSprites();
	InitSounds();
	InitScores();

	app.SetEventCallback(HandleEvents);
	app.SetRenderCallback(HandleRenders);

	app.StartAppLoop();

	FreeSprites();
	FreeSounds();
	FreeLabels();
	return 0;
}
