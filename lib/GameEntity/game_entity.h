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
	void SetPosition(const int x, const int y);
	void SetPosX(const int x);
	void SetPosY(const int y);
	void SetDimention(const int w, const int h);
	void SetWidth(const int w);
	void SetHeight(const int h);

	// Collider Setters:
	void SetPosition(const int index, const int x, const int y);
	void SetPosX(const int index, const int x);
	void SetPosY(const int index, const int y);
	void SetDimention(const int index, const int w, const int h);
	void SetWidth(const int index, const int w);
	void SetHeight(const int index, const int h);
	void SetColliderColorKey(SDL_Color key);
	void SetColliderColorKey(const int index, SDL_Color key);

	void SetUpdateCallback(void (*updateCallback)(void));
	void SetSpriteUpdateCallback(void (*updateCallback)(void));
	void SetColliderUpdateCallback(void (*updateCallback)(void));
	void SetColliderUpdateCallback(const int index, void (*updateCallback)(void));

	/* ================= GETTERS ================= */
	// Sprite Getters:
	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;
	
	// Collider Getters:
	Collider& GetCollider(const int index) const;
	int GetPosX(const int index) const;
	int GetPosY(const int index) const;
	int GetWidth(const int index) const;
	int GetHeight(const int index) const;

private:
	SDL_Renderer* m_renderer;
	TexturedRect* m_sprite;
	std::vector<Collider*> m_colliders;
	void (*m_updateCallback)(void);
};

#endif /* game_entity.h */
