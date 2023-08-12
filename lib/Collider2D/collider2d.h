#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include <SDL.h>

class Collider {
public:
	Collider();
	~Collider();

	void SetRect(const int x, const int y, const int w, const int h);
	void SetRect(const SDL_Rect& rect);

	void SetPosition(const int x, const int y);
	void SetPosX(const int x);
	void SetPosY(const int y);

	void SetDimention(const int w, const int h);
	void SetWidth(const int w);
	void SetHeight(const int h);

	void SetTop(const int x, const int y);
	void SetBottom(const int x, const int y);
	void SetLeft(const int x, const int y);
	void SetRight(const int x, const int y);
	void SetCenter(const int x, const int y);

	void SetColorKey(SDL_Color key);
	void SetUpdateCallback(void (*updateCallback)(void));

	SDL_Rect& GetCollider();
	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;

	int GetTopPosX() const;
	int GetTopPosY() const;

	int GetBottomPosX() const;
	int GetBottomPosY() const;
	
	int GetLeftPosX() const;
	int GetLeftPosY() const;

	int GetRightPosX() const;
	int GetRightPosY() const;

	int GetCenterPosX() const;
	int GetCenterPosY() const;

	SDL_bool IsColliding(const Collider& obj) const;
	void Update();
	void Render(SDL_Renderer* renderer);

private:
	SDL_Rect m_colliderRect;
	void (*m_updateCallback)(void);
	SDL_Color m_color;s
};

#endif /* collider2d.h */
