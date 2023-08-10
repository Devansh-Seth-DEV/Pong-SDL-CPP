#include "TEX_font.h"

bool TexturedFont::s_initialized = false;
ResourceManager* TexturedFont::s_resourceManager = ResourceManager::GetInstance();

TexturedFont::TexturedFont()
	: m_drawRect(false), m_label(""), m_surface(nullptr), m_texture(nullptr), m_font(nullptr), m_renderer(nullptr), m_updateCallback(nullptr), fontFile("")
{}

TexturedFont::TexturedFont(SDL_Renderer* renderer, const char* fontFilePath, const int fontSize, const char* label, SDL_Color& fg)
	: m_drawRect(false), m_updateCallback(nullptr)
{
	Label(renderer, fontFilePath, fontSize, label, fg);
}

void TexturedFont::Label(SDL_Renderer* renderer, const char* fontFilePath, const int fontSize, const char* label, SDL_Color& fg) {
	if(!s_initialized && TTF_Init() < 0) {
		std::cerr << "TTF fonts initialization error: " << TTF_GetError() << std::endl;
	} else {
		std::cout << "TTF fonts initialized" << std::endl;
		s_initialized = true;
	}

	fontFile = fontFilePath;
	m_label.erase();
	m_label.assign(label);

	m_font = s_resourceManager->GetFont(fontFilePath, fontSize);
	m_surface = TTF_RenderText_Solid(m_font, m_label.c_str(), fg);
	m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
	
	m_renderer = renderer;
	m_rectangle.x = 0;
	m_rectangle.y = 0;
	m_rectangle.w = 10;
	m_rectangle.h = 10;
	m_fg = fg;
}

TexturedFont::~TexturedFont() {
	s_resourceManager->FreeFontResources(fontFile);
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	m_font = nullptr;
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

void TexturedFont::SetRect(const SDL_Rect& rect) {
	m_rectangle = rect;
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

void TexturedFont::SetLabel(const char* label) {
	SDL_DestroyTexture(m_texture);
	m_label.erase();
	m_label.assign(label);

	m_surface = TTF_RenderText_Solid(m_font, m_label.c_str(), m_fg);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
}	

void TexturedFont::SetLabelColor(SDL_Color fg) {
	SDL_DestroyTexture(m_texture);
	
	m_surface = TTF_RenderText_Solid(m_font, m_label.c_str(), fg);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	m_fg = fg;
}

void TexturedFont::SetDrawRect(const bool flag) {
	m_drawRect = flag;
}

void TexturedFont::SetUpdateCallback(void (*updateCallback)(void)) {
	m_updateCallback = updateCallback;
}

SDL_Rect& TexturedFont::GetRect() {
	return m_rectangle;
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

void TexturedFont::Render() {
	if(m_drawRect) {
		SDL_SetRenderDrawColor(m_renderer, m_fg.r, m_fg.g, m_fg.g, m_fg.a);
		SDL_RenderDrawRect(m_renderer, &m_rectangle);
	}
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_rectangle);
}

void TexturedFont::Update() {
	if(m_updateCallback != nullptr) {
		m_updateCallback();
	}
}
