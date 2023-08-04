//third party lib
#include <SDL.h>
#include <manager.h>
#include <iostream>

class TexturedRect {
public:
	TexturedRect(SDL_Renderer* renderer, std::string sourcePath);

	~TexturedRect();

	void SetRect(const int x, const int y, const int w, const int h);
	void SetWidth(const int w);
   	void SetHeight(const int h);
	void SetPosX(const int x);
	void SetPosY(const int y);

	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;

	void Render(SDL_Renderer* renderer, SDL_Rect& sourceRect);
	void Update(void (*updateCallback)(void));

private:
	static ResourceManager& s_resourceManager;
	SDL_Rect m_rectangle;
	SDL_Texture* m_texture;
	void (*m_updateCallback)(void);
};
