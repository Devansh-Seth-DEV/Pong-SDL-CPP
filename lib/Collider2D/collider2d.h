#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include <SDL.h>

class Collider {
public:
	Collider();
	~Collider();

	void SetAbsolutePos(const int x, const int y);
	void SetDimention(const int w, const int h);
	
	SDL_Rect& GetCollider() const;
	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;

	SDL_bool IsColliding(const Collider& obj) const;
	void Update();
	void Render(SDL_Renderer* renderer, SDL_Rect* sourceRect);

private:
	SDL_Rect* m_colliderRect;	
};

#endif /* collider2d.h */
