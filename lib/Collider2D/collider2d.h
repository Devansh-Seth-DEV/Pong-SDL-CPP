#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include <SDL.h>

class Collider {
public:
	Collider();
	~Collider();

	void SetPosition(const int x, const int y);
	void SetDimention(const int w, const int h);
	void SetColorKey(SDL_Color key);
	void SetUpdateCallback(void (*updateCallback)(void));

	SDL_Rect& GetCollider() const;
	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;

	SDL_bool IsColliding(const Collider& obj) const;
	void Update();
	void Render(SDL_Renderer* renderer);

private:
	SDL_Rect* m_colliderRect;
	void (*m_updateCallback)(void);
	SDL_Color m_color;
};

#endif /* collider2d.h */
