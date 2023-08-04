#include "TEX_rect.h"

ResourceManager& TexturedRect::s_resourceManager = ResourceManager::GetInstance();

TexturedRect::TexturedRect(SDL_Renderer* renderer, std::string sourcePath) {
	SDL_Surface* surface = s_resourceManager.GetSurface(sourcePath);
	if(surface == nullptr) {
		std::cerr << "Textured Rectangle Surface Error: " << SDL_GetError() << std::endl;
	}

	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
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

void TexturedRect::Render(SDL_Renderer* renderer, SDL_Rect& sourceRect) {
	SDL_RenderCopy(renderer, m_texture, &sourceRect, &m_rectangle);
}

void TexturedRect::Update(void (*updateCallback)(void)) {
	m_updateCallback = updateCallback;
}
