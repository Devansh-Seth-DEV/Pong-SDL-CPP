#ifndef TEX_FONT_H
#define TEX_FONT_H

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <manager.h>

class TexturedFont {
public:
	TexturedFont(SDL_Renderer* renderer, std::string fontFilePath, const int fontSize, std::string label, SDL_Color fg);

	~TexturedFont();
	static void Quit();

	void SetRect(const int x, const int y, const int w, const int h);
	void SetPosX(const int x);
	void SetPoxY(const int y);
	void SetWidth(const int w);
	void SetHeight(const int h);
	void SetLabel(std::string label);
	void SetLabelColor(SDL_Color fg);

	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;
	SDL_Color GetLabelColor() const;
	std::string GetLabel() const;

	void Render(SDL_Renderer* renderer);
	void Update();

private:
	static bool s_initialized;
	static ResourceManager& s_resourceManager;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
	TTF_Font* m_font;
	SDL_Rect m_rectangle;
	std::string m_label;
	SDL_Color m_fg;
};

#endif /* TEX_font.h */
