#include "TEX_font.h"

bool TexturedFont::s_initialized = false;
ResourceManager& TexturedFont::s_resourceManager = ResourceManager::GetInstance();

TexturedFont::TexturedFont(SDL_Renderer* renderer, std::string fontFilePath, const int fontSize, std::string label, SDL_Color fg) {
	if(!s_initialized && TTF_Init() < 0) {
		std::cerr << "TTF fonts initialization error: " << TTF_GetError() << std::endl;
	} else {
		std::cout << "TTF fonts initialized" << std::endl;
		s_initialized = true;
	}

	m_font = s_resourceManager.GetFont(fontFilePath, fontSize);
	m_surface = TTF_RenderText_Solid(m_font, label.c_str(), fg);
	
	m_rectangle.x = 0;
	m_rectangle.y = 0;
	m_rectangle.w = 10;
	m_rectangle.h = 10;
	m_label = label;
	m_fg = fg;
}

TexturedFont::~TexturedFont() {
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}

void TexturedFont::Quit() {
	TTF_Quit();
	s_initialized = false;
}

void TexturedFont::SetRect(const int x, const int y, const int w, const int h) {
	m_rectangle.x = x;
	m_rectangle.y = y;
	m_rectangle.w = w;
	m_rectangle.h = h;
}

void TexturedFont::SetPosX(const int x) {
	m_rectangle.x = x;
}

void TexturedFont::SetPosY(const int y) {
	m_rectangle.y = y;
}

void TexturedFont::SetWidth(const int w) {
	m_rectangle.w = w;
}

void TexturedFont::SetHeight(const int h) {
	m_rectangle.h = h;
}

void TexturedFont::SetLabel(std::string label) {
	SDL_FreeSurface(m_surface);

	m_surface = TTF_RenderText_Solid(m_font, label.c_str(), m_fg);
   	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	m_label = label;
}	

void TexturedFont::SetLabelColor(SDL_Color fg) {
	SDL_FreeSurface(m_surface);
	
	m_surface = TTF_RenderText_Solid(m_font, m_label.c_str(), fg);
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	m_fg = fg;
}

int TexturedFont::GetPosX() const {
	return m_rectangle.x;
}

int TexturedFont::GetPosY() const {
	return m_rectangle.y;
}

int TexturedFont::GetWidth() const {
	return m_rectangle.w;
}

int TexturedFont::GetHeight() const {
	return m_rectangle.h;
}

SDL_Color TexturedFont::GetLabelColor() const {
	return m_fg;
}

std::string TexturedFont::GetLabel() const {
	return m_label;
}

void TexturedFont::Render(SDL_Renderer* renderer) {
	if(m_texture == nullptr) {
		m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
		SDL_FreeSurface(m_surface);
		m_surface = nullptr;
	}

	SDL_RenderCopy(renderer, m_texture, nullptr, &m_rectangle);
}

void TexturedFont::Update() {

}
