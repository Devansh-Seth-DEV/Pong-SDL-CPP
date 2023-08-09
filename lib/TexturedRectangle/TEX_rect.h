#ifndef TEX_RECT_H
#define TEX_RECT_H

#include <iostream>

#include <SDL.h>

#include <manager.h>

class TexturedRect {
public:
	TexturedRect();
	TexturedRect(SDL_Renderer* renderer, const char* sourcePath);
	TexturedRect(SDL_Renderer* renderer, const char* sourcePath, SDL_Color key);

	~TexturedRect();

	void SetRect(const int x, const int y, const int w, const int h);
	void SetRect(const SDL_Rect& rect);
	void SetPosition(const int x, const int y);
	void SetDimention(const int w, const int h);
	void SetWidth(const int w);
   	void SetHeight(const int h);
	void SetPosX(const int x);
	void SetPosY(const int y);
	void SetUpdateCallback(void (*updateCallback)(void));

	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;
	SDL_Rect& GetRect();

	void Update();
	void Render(SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer, SDL_Rect& sourceRect);

private:
	static ResourceManager* s_resourceManager;
	std::string resource;
	SDL_Rect m_rectangle;
	SDL_Texture* m_texture;
	SDL_Color m_colorKey;
	void (*m_updateCallback)(void);
};

#endif /* TEX_rect.h */
