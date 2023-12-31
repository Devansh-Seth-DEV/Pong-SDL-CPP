#include "game_entity.h"

Entity::Entity()
	: m_sprite(nullptr), m_renderer(nullptr), m_updateCallback(nullptr)
{}

Entity::Entity(SDL_Renderer* renderer)
	: m_sprite(nullptr), m_renderer(renderer), m_updateCallback(nullptr)
{}

Entity::~Entity() {
	delete m_sprite;
	for(int i=0; i<m_colliders.size(); i++) {
		delete m_colliders[i];
	}
}

void Entity::Update() {
	if(m_updateCallback != nullptr) {
		m_updateCallback();
	}
	SpriteUpdate();
	ColliderUpdate();
}

void Entity::SpriteUpdate() {
	m_sprite->Update();
}

void Entity::ColliderUpdate() {
	for(int i=0; i<m_colliders.size(); i++) {
		m_colliders[i]->Update();
	}
}

void Entity::ColliderUpdate(const int index) {
	m_colliders[index]->Update();
}

void Entity::Render() {
	m_sprite->Render(m_renderer);
	for(int i=0; i<m_colliders.size(); i++) {
		m_colliders[i]->Render(m_renderer);
	}
}

void Entity::RenderSprite() {
	m_sprite->Render(m_renderer);
}

void Entity::RenderCollider() {
	for(int i=0; i<m_colliders.size(); i++) {
		m_colliders[i]->Render(m_renderer);
	}
}

void Entity::RenderCollider(const int index) {
	if(m_colliders.size() > 0) {
		m_colliders[index]->Render(m_renderer);
	}
}

void Entity::AddRenderer(SDL_Renderer* renderer) {
	m_renderer = renderer;
}

void Entity::AddSprite(const char* spritePath) {
	m_sprite = new TexturedRect(m_renderer, spritePath);
	m_sprite->SetRect(0, 0, 0, 0);
}

void Entity::AddSprite(const char* spritePath, SDL_Color key) {
	m_sprite = new TexturedRect(m_renderer, spritePath, key);
	m_sprite->SetRect(0, 0, 0, 0);
}

void Entity::AddCollider2D() {
	Collider* collider = new Collider();
	m_colliders.push_back(collider);
}

void Entity::AddCollider2D(const int x, const int y, const int w, const int h) {
	Collider* collider = new Collider();
	collider->SetRect(x, y, w, h);
	m_colliders.push_back(collider);
}

SDL_bool Entity::IsColliding(const Entity& obj) {
	SDL_bool flag = SDL_FALSE;
	int loop = (obj.m_colliders.size() > m_colliders.size()) ? obj.m_colliders.size() : m_colliders.size();

	for(int i=0; i<loop; i++) {
		Collider& collider1 = *m_colliders[i];
		Collider* collider2 = obj.m_colliders[i];
		flag = collider1.IsColliding(*collider2);
		if(flag) {
			break;
		}
	}

	return flag;
}

void Entity::SetRect(const int x, const int y, const int w, const int h) {
	m_sprite->SetRect(x, y, w, h);
}

void Entity::SetRect(SDL_Rect& rect) {
	m_sprite->SetRect(rect);
}

void Entity::SetPosition(const int x, const int y) {
	m_sprite->SetPosition(x, y);
}

void Entity::SetPosX(const int x) {
	m_sprite->SetPosX(x);
}

void Entity::SetPosY(const int y) {
	m_sprite->SetPosY(y);
}

void Entity::SetDimention(const int w, const int h) {
	m_sprite->SetDimention(w, h);
}

void Entity::SetWidth(const int w) {
	m_sprite->SetWidth(w);
}

void Entity::SetHeight(const int h) {
	m_sprite->SetHeight(h);
}

void Entity::SetTop(const int x, const int y) {
	m_sprite->SetTop(x, y);
}

void Entity::SetBottom(const int x, const int y) {
	m_sprite->SetBottom(x, y);
}

void Entity::SetLeft(const int x, const int y) {
	m_sprite->SetLeft(x, y);
}

void Entity::SetRight(const int x, const int y) {
	m_sprite->SetRight(x, y);
}

void Entity::SetCenter(const int x, const int y) {
	m_sprite->SetCenter(x, y);
}

void Entity::SetRect(const int index, const int x, const int y, const int w, const int h) {
	m_colliders[index]->SetRect(x, y, w, h);
}

void Entity::SetRect(const int index, SDL_Rect& rect) {
	m_colliders[index]->SetRect(rect);
}

void Entity::SetPosition(const int index, const int x, const int y) {
	m_colliders[index]->SetPosition(x, y);
}

void Entity::SetPosX(const int index, const int x) {
	m_colliders[index]->SetPosX(x);
}

void Entity::SetPosY(const int index, const int y) {
	m_colliders[index]->SetPosY(y);
}

void Entity::SetDimention(const int index, const int w, const int h) {
	m_colliders[index]->SetDimention(w, h);
}

void Entity::SetWidth(const int index, const int w) {
	m_colliders[index]->SetWidth(w);
}

void Entity::SetHeight(const int index, const int h) {
	m_colliders[index]->SetHeight(h);
}

void Entity::SetTop(const int index, const int x, const int y) {
	m_colliders[index]->SetTop(x, y);
}

void Entity::SetBottom(const int index, const int x, const int y) {
	m_colliders[index]->SetBottom(x, y);
}

void Entity::SetLeft(const int index, const int x, const int y) {
	m_colliders[index]->SetLeft(x, y);
}

void Entity::SetRight(const int index, const int x, const int y) {
	m_colliders[index]->SetRight(x, y);
}

void Entity::SetCenter(const int index, const int x, const int y) {
	m_colliders[index]->SetCenter(x, y);
}

void Entity::SetColliderColorKey(SDL_Color key) {
	for(int i=0; i<m_colliders.size(); i++) {
		m_colliders[i]->SetColorKey(key);
	}
}

void Entity::SetColliderColorKey(const int index, SDL_Color key) {
	m_colliders[index]->SetColorKey(key);
}

void Entity::SetUpdateCallback(void (*updateCallback)(void)) {
	m_updateCallback = updateCallback;
}

void Entity::SetSpriteUpdateCallback(void (*updateCallback)(void)) {
	m_sprite->SetUpdateCallback(updateCallback);
}

void Entity::SetColliderUpdateCallback(void (*updateCallback)(void)) {
	for(int i=0; i<m_colliders.size(); i++) {
		m_colliders[i]->SetUpdateCallback(updateCallback);
	}
}

void Entity::SetColliderUpdateCallback(const int index, void (*updateCallback)(void)) {
	m_colliders[index]->SetUpdateCallback(updateCallback);
}

SDL_Rect& Entity::GetRect() {
	return m_sprite->GetRect();
}

int Entity::GetPosX() const {
	return m_sprite->GetPosX();
}

int Entity::GetPosY() const {
	return m_sprite->GetPosY();
}

int Entity::GetWidth() const {
	return m_sprite->GetWidth();
}

int Entity::GetHeight() const {
	return m_sprite->GetHeight();
}

int Entity::GetTopPosX() const {
	return m_sprite->GetTopPosX();
}

int Entity::GetTopPosY() const {
	return m_sprite->GetTopPosY();
}

int Entity::GetBottomPosX() const {
	return m_sprite->GetBottomPosX();
}

int Entity::GetBottomPosY() const {
	return m_sprite->GetBottomPosY();
}

int Entity::GetLeftPosX() const {
	return m_sprite->GetLeftPosX();
}

int Entity::GetLeftPosY() const {
   return m_sprite->GetLeftPosY();
}

int Entity::GetRightPosX() const {
	return m_sprite->GetRightPosX();
}

int Entity::GetRightPosY() const {
	return m_sprite->GetRightPosY();
}

int Entity::GetCenterPosX() const {
	return m_sprite->GetCenterPosX();
}

int Entity::GetCenterPosY() const {
	return m_sprite->GetCenterPosY();
}

Collider& Entity::GetCollider(const int index) const {
	return *m_colliders[index];
}

int Entity::GetPosX(const int index) const {
	return m_colliders[index]->GetPosX();
}

int Entity::GetPosY(const int index) const {
	return m_colliders[index]->GetPosY();
}

int Entity::GetWidth(const int index) const {
	return m_colliders[index]->GetWidth();
}

int Entity::GetHeight(const int index) const {
	return m_colliders[index]->GetHeight();
}

int Entity::GetTopPosX(const int index) const {
	return m_colliders[index]->GetTopPosX();
}

int Entity::GetTopPosY(const int index) const {
	return m_colliders[index]->GetTopPosY();
}

int Entity::GetBottomPosX(const int index) const {
	return m_colliders[index]->GetBottomPosX();
}

int Entity::GetBottomPosY(const int index) const {
	return m_colliders[index]->GetBottomPosY();
}

int Entity::GetLeftPosX(const int index) const {
	return m_colliders[index]->GetLeftPosX();
}

int Entity::GetLeftPosY(const int index) const {
   return m_colliders[index]->GetLeftPosY();
}

int Entity::GetRightPosX(const int index) const {
	return m_colliders[index]->GetRightPosX();
}

int Entity::GetRightPosY(const int index) const {
	return m_colliders[index]->GetRightPosY();
}

int Entity::GetCenterPosX(const int index) const {
	return m_colliders[index]->GetCenterPosX();
}

int Entity::GetCenterPosY(const int index) const {
	return m_colliders[index]->GetCenterPosY();
}

