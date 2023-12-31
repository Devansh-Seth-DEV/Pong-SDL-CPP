#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <vector>
#include <SDL.h>
#include <TEX_rect.h>
#include <collider2d.h>

class Entity {
public:
	Entity();
	Entity(SDL_Renderer* renderer);

	~Entity();

	/* ================= METHODS ================= */
	void Update();
	void SpriteUpdate();
	void ColliderUpdate();
	void ColliderUpdate(const int index);
	void Render();
	void RenderSprite();
	void RenderCollider();
	void RenderCollider(const int index);

	void AddRenderer(SDL_Renderer* renderer);
	void AddSprite(const char* spritePath);
	void AddSprite(const char* spritePath, SDL_Color key);
	void AddCollider2D();
	void AddCollider2D(const int x, const int y, const int w, const int h);

	SDL_bool IsColliding(const Entity& obj);


	/* ================= SETTERS ================= */
	// Sprite Setters:
	void SetRect(const int x, const int y, const int w, const int h);
	void SetRect(SDL_Rect& rect);

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

	// Collider Setters:
	void SetRect(const int index, const int x, const int y, const int w, const int h);
	void SetRect(const int index, SDL_Rect& rect);

	void SetPosition(const int index, const int x, const int y);
	void SetPosX(const int index, const int x);
	void SetPosY(const int index, const int y);

	void SetDimention(const int index, const int w, const int h);
	void SetWidth(const int index, const int w);
	void SetHeight(const int index, const int h);

	void SetTop(const int index, const int x, const int y);
	void SetBottom(const int index, const int x, const int y);
	void SetLeft(const int index, const int x, const int y);
	void SetRight(const int index, const int x, const int y);
	void SetCenter(const int index, const int x, const int y);

	void SetColliderColorKey(SDL_Color key);
	void SetColliderColorKey(const int index, SDL_Color key);

	void SetUpdateCallback(void (*updateCallback)(void));
	void SetSpriteUpdateCallback(void (*updateCallback)(void));
	void SetColliderUpdateCallback(void (*updateCallback)(void));
	void SetColliderUpdateCallback(const int index, void (*updateCallback)(void));

	/* ================= GETTERS ================= */
	// Sprite Getters:
	SDL_Rect& GetRect();

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
	
	// Collider Getters:
	Collider& GetCollider(const int index) const;

	int GetPosX(const int index) const;
	int GetPosY(const int index) const;
	int GetWidth(const int index) const;
	int GetHeight(const int index) const;

	int GetTopPosX(const int index) const;
	int GetTopPosY(const int index) const;

	int GetBottomPosX(const int index) const;
	int GetBottomPosY(const int index) const;

	int GetLeftPosX(const int index) const;
	int GetLeftPosY(const int index) const;

	int GetRightPosX(const int index) const;
	int GetRightPosY(const int index) const;

	int GetCenterPosX(const int index) const;
	int GetCenterPosY(const int index) const;

private:
	SDL_Renderer* m_renderer;
	TexturedRect* m_sprite;
	std::vector<Collider*> m_colliders;
	void (*m_updateCallback)(void);
};

#endif /* game_entity.h */
