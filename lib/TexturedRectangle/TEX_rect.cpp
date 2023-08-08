#include "TEX_rect.h"

ResourceManager& TexturedRect::s_resourceManager = ResourceManager::GetInstance();

TexturedRect::TexturedRect()
	: m_updateCallback(nullptr)
{}

TexturedRect::TexturedRect(SDL_Renderer* renderer, const char* sourcePath)
	: m_updateCallback(nullptr)
{
	//std::string path = sourcePath;
	SDL_Surface& surface = s_resourceManager.GetSurface(sourcePath);
	m_texture = SDL_CreateTextureFromSurface(renderer, &surface);
}

TexturedRect::TexturedRect(SDL_Renderer* renderer, const char* sourcePath, SDL_Color key)
	: m_updateCallback(nullptr)
{
	//std::string path = sourcePath;
	SDL_Surface& surface = s_resourceManager.GetSurface(sourcePath);

	SDL_SetColorKey(&surface, SDL_TRUE, SDL_MapRGB(surface.format, key.r, key.g, key.b));
	
	m_texture = SDL_CreateTextureFromSurface(renderer, &surface);

	m_colorKey = key;
}

TexturedRect::~TexturedRect() {
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
