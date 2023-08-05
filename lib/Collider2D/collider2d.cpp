#include "collider2d.h"

Collider::Collider() {
	m_color = {255, 255, 255, SDL_ALPHA_OPAQUE};
	m_colliderRect = new SDL_Rect;
	SetAbsolutePos(0, 0);
	SetDimention(0, 0);
}

Collider::~Collider() {
	delete m_colliderRect;
	m_colliderRect = nullptr;
}

void Collider::SetPosition(const int x, const int y) {
	m_colliderRect->x = x;
	m_colliderRect->y = y;
}

void Collider::SetDimention(const int w, const int h) {
	m_colliderRect->w = w;
	m_colliderRect->h = h;
}

void Collider::SetColorKey(SDL_Color key) {
	m_color = key;
}

void SetUpdateCallback(void (*updateCallback)(void)) {
	m_updateCallback = updateCallback;
}

SDL_Rect& Collider::GetCollider() const {
	return *m_colliderRect;
}

int Collider::GetPosX() const {
	return m_colliderRect->x;
}

int Collider::GetPosY() const {
	return m_colliderRect->y;
}

int Collider::GetWidth() const {
	return m_colliderRect->w;
}

int Collider::GetHeight() const {
	return m_colliderRect->h;
}

SDL_bool IsColliding(const Collider& obj) const {
	if(m_colliderRect == nullptr || obj.m_colliderRect == nullptr) {
		return SDL_FALSE;
	} else {
		return SDL_HasIntersection(m_colliderRect, obj.m_colliderRect);
	}
}

void Collider::Update() {
	m_updateCallback();
}

void Collider::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, m_color[0], m_color[1], m_color[2], m_color[3]);
	SDL_RenderDrawRect(renderer, m_colliderRect);
}