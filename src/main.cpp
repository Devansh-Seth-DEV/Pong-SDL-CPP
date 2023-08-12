#include <iostream>

//custom static libraries
#include <engine.h>
#include <TEX_font.h>
#include <game_entity.h>
#include <audio_mixer.h>

#define PADDLE_SPRITE "./assets/images/pong/paddle-green.bmp"
#define BALL_SPRITE "./assets/images/pong/ball.bmp"
#define COURT_SPRITE "./assets/images/pong/court.bmp"
#define ICON "./assets/images/pong/icon.bmp"
#define FONT_FILE "./assets/fonts/Open_24_Display_St.ttf"
#define COLLISION_SOUND "./assets/sounds/collision.wav"
#define SCORE_SOUND "./assets/sounds/score.wav"
#define FONT_SIZE 16

// global variables
SDLApp app;

Entity* leftPaddle;
Entity* rightPaddle;
Entity* ball;
Entity* court;

Mixer* collisionSound;
Mixer* scoreSound;

TexturedFont* leftScoreLabel;
TexturedFont* rightScoreLabel;

SDL_Color fontFg = {255, 255, 255, SDL_ALPHA_OPAQUE};

struct GameState {
	float movementSpeed;
	float ballSpeed;
	int ballXDirection;
	int ballYDirection;
	int leftScore;
	int rightScore;
	bool updateRightScore;
	bool updateLeftScore;
	bool bounceBall;
};

struct PaddleState {
	bool goUp;
	bool goDown;
};

GameState* gameState;
PaddleState leftPaddleState;
PaddleState rightPaddleState;

void FreeSprites() {
	delete court;
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

std::string GetLeftScore() {
	return std::string("LEFT " + std::to_string(gameState->leftScore));
}

std::string GetRightScore() {
	return std::string("RIGHT " + std::to_string(gameState->rightScore));
}

void InitSprites() {
	SDL_Rect paddle = {0, app.GetHeight()/2-(128/2), 32, 128};
	SDL_Rect ballRect = {app.GetWidth()/2, app.GetHeight()/2, 20, 20};
	ballRect.x += ballRect.w/2;
	ballRect.y += ballRect.h/2;

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

	court = new Entity(app.GetRenderer());
	court->AddSprite(COURT_SPRITE);
	court->SetRect(0, 0, app.GetWidth(), app.GetHeight());
}

void InitSounds() {
	collisionSound = new Mixer(COLLISION_SOUND);
	collisionSound->SetupDevice();

	scoreSound = new Mixer(SCORE_SOUND);
	scoreSound->SetupDevice();
}

void InitScores() {
	SDL_Rect scoreRect = {leftPaddle->GetPosX()+leftPaddle->GetWidth(), 0, 70, FONT_SIZE};

	leftScoreLabel = new TexturedFont(app.GetRenderer(), FONT_FILE, FONT_SIZE, "", fontFg);
	leftScoreLabel->SetRect(scoreRect);
	leftScoreLabel->SetDrawRect(false);
	leftScoreLabel->SetLabel(GetLeftScore().c_str());
	
	rightScoreLabel = new TexturedFont(app.GetRenderer(), FONT_FILE, FONT_SIZE, "", fontFg);
	rightScoreLabel->SetRect(rightPaddle->GetPosX()-scoreRect.w-10, scoreRect.y, scoreRect.w, scoreRect.h);
	rightScoreLabel->SetDrawRect(false);
	rightScoreLabel->SetLabel(GetRightScore().c_str());
}


void HandleScoreUpdates() {
	if(gameState->updateLeftScore) {
		gameState->leftScore++;
		leftScoreLabel->SetLabel(GetLeftScore().c_str());
		gameState->updateLeftScore = false;
		gameState->bounceBall = false;
	}
	if(gameState->updateRightScore) {
		gameState->rightScore++;
		rightScoreLabel->SetLabel(GetRightScore().c_str());
		gameState->updateRightScore = false;
		gameState->bounceBall = false;
	}
}

void HandlePaddleUpdates() {
	int leftPaddleY = leftPaddle->GetPosY();
	int rightPaddleY = rightPaddle->GetPosY();
	if(leftPaddleState.goUp) {
		if(leftPaddle->GetTopPosY()-gameState->movementSpeed <= 0) {
			leftPaddleY = 0;
		} else {
			leftPaddleY -= gameState->movementSpeed;
		}
		leftPaddleState.goUp = false;
	} else if(leftPaddleState.goDown) {
		if(leftPaddle->GetBottomPosY()+gameState->movementSpeed >= app.GetHeight()) {
			leftPaddleY = app.GetHeight()-leftPaddle->GetHeight();
		} else {
			leftPaddleY += gameState->movementSpeed;
		}
		leftPaddleState.goDown = false;
	} else {
		leftPaddleY += 0;
	}

	if(rightPaddleState.goUp) {
		if(rightPaddle->GetTopPosY()-gameState->movementSpeed <= 0) {
			rightPaddleY = 0;
		} else {
			rightPaddleY -= gameState->movementSpeed;
		}
		rightPaddleState.goUp = false;
	} else if(rightPaddleState.goDown) {
		if(rightPaddle->GetBottomPosY()+gameState->movementSpeed >= app.GetHeight()) {
			rightPaddleY = app.GetHeight()-rightPaddle->GetHeight();
		} else {
			rightPaddleY += gameState->movementSpeed;
		}
		rightPaddleState.goDown = false;
	} else {
		rightPaddleY += 0;
	}

	leftPaddle->SetPosY(leftPaddleY);
	leftPaddle->SetPosY(0, leftPaddleY);
	rightPaddle->SetPosY(rightPaddleY);
	rightPaddle->SetPosY(0, rightPaddleY);
}

void HandleBallUpdates() {
	if(gameState->bounceBall) {
		if(leftPaddle->IsColliding(*ball)) {
			gameState->ballXDirection *= -1;	
		} else if(rightPaddle->IsColliding(*ball)) {
			gameState->ballXDirection *= -1;
		}

		int ballPosX = ball->GetPosX();
		int ballPosY = ball->GetPosY();

		if(ball->GetRightPosX() >= app.GetWidth()) {
			gameState->ballXDirection *= -1;
			gameState->updateLeftScore = true;
		} else if(ball->GetLeftPosX() <= 0) {
			gameState->ballXDirection *= -1;
			gameState->updateRightScore = true;
		}

		if(ball->GetBottomPosY() >= app.GetHeight()) {
			gameState->ballYDirection *= -1;
		} else if(ball->GetTopPosY() <= 0) {
			gameState->ballYDirection *= -1;
		}

		if(gameState->ballXDirection > 0) {
			ballPosX += gameState->ballSpeed;
		} else {
			ballPosX -= gameState->ballSpeed;
		}

		if(gameState->ballYDirection > 0) {
			ballPosY += gameState->ballSpeed;
		} else {
			ballPosY -= gameState->ballSpeed;
		}


		ball->SetPosition(ballPosX, ballPosY);
		ball->SetPosition(0, ball->GetPosX(), ball->GetPosY());
	} else {
		if(gameState->updateRightScore) {
			gameState->ballXDirection = -1;
		} else {
			gameState->ballXDirection = 1;
		}
		gameState->ballYDirection *= -1;
		ball->SetCenter(app.GetWidth()/2, app.GetHeight()/2);
		ball->SetPosition(0, ball->GetPosX(), ball->GetPosY());
	}
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
				leftPaddleState = {true, false};
			} else if(event.key.keysym.sym == SDLK_s) {
				// change left paddle position in downward direction
				leftPaddleState = {false, true};
			}
			
			if(event.key.keysym.sym == SDLK_i) {
				// change right paddle position in upward direction
				rightPaddleState = {true, false};
			} else if(event.key.keysym.sym == SDLK_k) {
				// change right paddle position in downward direction
				rightPaddleState = {false, true};
			}

			if(event.key.keysym.sym == SDLK_RETURN) {
				gameState->bounceBall = true;
			}
		}	
	}
}

void HandleUpdates() {
	leftPaddle->Update();
	rightPaddle->Update();
	ball->Update();
	leftScoreLabel->Update();
	rightScoreLabel->Update();
}

void HandleRenders() {
	court->RenderSprite();

	leftScoreLabel->Render();
	rightScoreLabel->Render();

	leftPaddle->Render();
	rightPaddle->Render();
	ball->Render();
}

int main() {
	const char* title = "PONG";
	app.App(title, 20, 20, 640, 480, SDL_WINDOW_SHOWN, SDL_INIT_VIDEO | SDL_INIT_AUDIO, -1, SDL_RENDERER_ACCELERATED);
	app.SetIcon(ICON);

	gameState = new GameState;
	gameState->movementSpeed 	= 5.0f;
	gameState->ballSpeed 	 	= 2.0f;
	gameState->ballXDirection 	= 1;
	gameState->ballYDirection 	= 1;
	gameState->leftScore 	 	= 0;
	gameState->rightScore 	 	= 0;
	gameState->updateLeftScore  = false;
	gameState->updateRightScore = false;
	gameState->bounceBall		= false;

	leftPaddleState = {false, false};
	rightPaddleState = leftPaddleState;

	InitSprites();
	InitSounds();
	InitScores();
	
	leftPaddle->SetUpdateCallback(HandlePaddleUpdates);
	rightPaddle->SetUpdateCallback(HandlePaddleUpdates);
	ball->SetUpdateCallback(HandleBallUpdates);
	leftScoreLabel->SetUpdateCallback(HandleScoreUpdates);
	rightScoreLabel->SetUpdateCallback(HandleScoreUpdates);
	app.SetEventCallback(HandleEvents);
	app.SetUpdateCallback(HandleUpdates);
	app.SetRenderCallback(HandleRenders);

	app.StartAppLoop();

	FreeSprites();
	FreeSounds();
	FreeLabels();
	delete gameState;
	return 0;
}
