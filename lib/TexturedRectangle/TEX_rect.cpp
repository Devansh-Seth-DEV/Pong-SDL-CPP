#include "TEX_rect.h"

ResourceManager* TexturedRect::s_resourceManager = ResourceManager::GetInstance();

TexturedRect::TexturedRect()
	: m_updateCallback(nullptr)
{
	m_rectangle.x = {0, 0, 0, 0};
}

TexturedRect::TexturedRect(SDL_Renderer* renderer, const char* sourcePath)
	: m_updateCallback(nullptr)
{
	resource = sourcePath;
	m_rectangle = {0, 0, 0, 0};
	SDL_Surface* surface = s_resourceManager->GetImgSurface(sourcePath);
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	std::cout << "Created texture: " << sourcePath << std::endl;
}

TexturedRect::TexturedRect(SDL_Renderer* renderer, const char* sourcePath, SDL_Color key)
	: m_updateCallback(nullptr)
{
	m_colorKey = key;
	m_rectangle = {0, 0, 0, 0};
	SDL_Surface* surface = s_resourceManager->GetImgSurface(sourcePath);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, key.r, key.g, key.b));
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
}

TexturedRect::~TexturedRect() {
	s_resourceManager->FreeImgResources(resource);
	SDL_DestroyTexture(m_texture);
	m_updateCallback = nullptr;
}

void TexturedRect::SetRect(const int x, const int y, const int w, const int h) {
	m_rectangle.x = x;
	m_rectangle.y = y;
	m_rectangle.w = w;
	m_rectangle.h = h;
}

void TexturedRect::SetRect(const SDL_Rect& rect) {
	m_rectangle = rect;
}

void TexturedRect::SetPosition(const int x, const int y) {
	m_rectangle.x = x;
	m_rectangle.y = y;
}

void TexturedRect::SetDimention(const int w, const int h) {
	m_rectangle.w = w;
	m_rectangle.h = h;
}

void TexturedRect::SetWidth(const int w) {
	m_rectangle.w = w;
}

void TexturedRect::SetHeight(const int h) {
	m_rectangle.h = h;
}

void TexturedRect::SetPosX(const int x) {
	m_rectangle.x = x;
}

void TexturedRect::SetPosY(const int y) {
	m_rectangle.y = y;
}

void TexturedRect::SetTop(const int x, const int y) {
	m_rectangle.x = x-m_rectangle.w/2;
	m_rectangle.y = y;
}

void TexturedRect::SetBottom(const int x, const int y) {
	m_rectangle.x = x-m_rectangle.w/2;
	m_rectangle.y = y-m_rectangle.h;
}

void TexturedRect::SetLeft(const int x, const int y) {
	m_rectangle.x = x;
	m_rectangle.y = y-m_rectangle.h/2;
}

void TexturedRect::SetRight(const int x, const int y) {
	m_rectangle.x = x-m_rectangle.w;
	m_rectangle.y = y-m_rectangle.h/2;
}

void TexturedRect::SetCenter(const int x, const int y) {
	m_rectangle.x = x-m_rectangle.w/2;
	m_rectangle.y = y-m_rectangle.h/2;
}

void TexturedRect::SetUpdateCallback(void (*updateCallback)(void)) {
	m_updateCallback = updateCallback;
}

int TexturedRect::GetPosX() const {
	return m_rectangle.x;
}

int TexturedRect::GetPosY() const {
	return m_rectangle.y;
}

int TexturedRect::GetWidth() const {
	return m_rectangle.w;
}

int TexturedRect::GetHeight() const {
	return m_rectangle.h;
}

int TexturedRect::GetTopPosX() const {
	return m_rectangle.x + m_rectangle.w/2;
}

int TexturedRect::GetTopPosY() const {
	return m_rectangle.y;
}

int TexturedRect::GetBottomPosX() const {
	return m_rectangle.x+m_rectangle.w/2;
}

int TexturedRect::GetBottomPosY() const {
	return m_rectangle.y + m_rectangle.h;
}

int TexturedRect::GetLeftPosX() const {
	return m_rectangle.x;
}

int TexturedRect::GetLeftPosY() const {
	return m_rectangle.y + m_rectangle.h/2;
}

int TexturedRect::GetRightPosX() const {
	return m_rectangle.x + m_rectangle.w;
}

int TexturedRect::GetRightPosY() const {
	return m_rectangle.y + m_rectangle.h/2;
}

int TexturedRect::GetCenterPosX() const {
	return m_rectangle.x + m_rectangle.w/2;
}

int TexturedRect::GetCenterPosY() const {
	return m_rectangle.y + m_rectangle.h/2;
}

SDL_Rect& TexturedRect::GetRect() {
	return m_rectangle;
}

void TexturedRect::Update() {
	if(m_updateCallback != nullptr) {
		m_updateCallback();
	}
}

void TexturedRect::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, nullptr, &m_rectangle);
}

void TexturedRect::Render(SDL_Renderer* renderer, SDL_Rect& sourceRect) {
	SDL_RenderCopy(renderer, m_texture, &sourceRect, &m_rectangle);
}
