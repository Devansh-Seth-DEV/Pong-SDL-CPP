#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <vector>
#include <SDL.h>
#include <TEX_rect.h>

class Entity {
public:
	Entity();
	Entity(SDL_Renderer* renderer);

	~Entity();

	void Update();
	void Render();

	void AddTexturedRect(const char* spritePath);
	void AddTexturedRect(const char* spritePath, SDL_Color key);
	void AddCollider2D();
	SDL_bool IsColliding(const Entity& obj);

	void SetPosition(const int x, const int y);
	void SetPosX(const int x);
	void SetPoxY(const int y);
	void SetDimention(const int w, const int h);
	void SetWidth(const int w);
	void SetHeight(const int h);

	Collider& GetCollider(const int index) const;
	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetColliderPosX(const int index) const;
	int GetColliderPosY(const int index) const;
	int GetColliderWidth(const int index) const;
	int GetColliderHeight(const int index) const;

private:
	SDL_Renderer* m_renderer;
	TexturedRect* m_sprite;
	std::vector<Collider*> m_colliders;
};

#endif /* game_entity.h */
