#ifndef TEX_FONT_H
#define TEX_FONT_H

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <manager.h>

class TexturedFont {
public:
	TexturedFont();
	TexturedFont(SDL_Renderer* renderer, const char* fontFilePath, const int fontSize, const char* label, SDL_Color& fg);
	void Label(SDL_Renderer* renderer, const char* fontFilePath, const int fontSize, const char* label, SDL_Color& fg);

	~TexturedFont();
	static void Quit();

	void SetRect(const int x, const int y, const int w, const int h);
	void SetPosX(const int x);
	void SetPosY(const int y);
	void SetWidth(const int w);
	void SetHeight(const int h);
	void SetLabel(const char* label);
	void SetLabelColor(SDL_Color fg);

	SDL_Rect& GetRect();
	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;
	SDL_Color GetLabelColor() const;
	std::string GetLabel() const;

	void Render();
	void Render(bool showBorder);
	void Update();

private:
	static bool s_initialized;
	static ResourceManager* s_resourceManager;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
	SDL_Renderer* m_renderer;
	TTF_Font* m_font;
	SDL_Rect m_rectangle;
	std::string m_label;
	SDL_Color m_fg;
	bool m_drawRect;
};

#endif /* TEX_font.h */
