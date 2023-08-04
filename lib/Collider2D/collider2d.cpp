#include "collider2d.h"

Collider::Collider() {
	m_colliderRect = new SDL_Rect;
	SetAbsolutePos(0, 0);
	SetDimention(0, 0);
}

Collider::~Collider() {
	delete m_colliderRect;
	m_colliderRect = nullptr;
}

void Collider::SetAbsolutePos(const int x, const int y) {
	m_colliderRect->x = x;
	m_colliderRect->y = y;
}

void Collider::SetDimention(const int w, const int h) {
	m_colliderRect->w = w;
	m_colliderRect->h = h;
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

void Collider::Update()
{}

void Collider::Render(SDL_Renderer* renderer, SDL_Rect* sourceRect)
{}
