#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

//third party lib
#include <SDL.h>
#include <SDL_ttf.h>

class ResourceManager {
public:
	~ResourceManager();

	static ResourceManager& GetInstance();
	SDL_Surface* GetSurface(std::string sourcePath);
	TTF_Font* GetFont(const char* fontFilePath, const int fontSize);

private:
	ResourceManager();
	ResourceManager(const ResourceManager& manager);
	ResourceManager operator=(const ResourceManager& manager);
	static ResourceManager* Instance();

private:
	std::unordered_map<std::string, SDL_Surface*> m_surfaces;
	std::unordered_map<std::string, TTF_Font*> m_fonts;
};

#endif /* manager.h */
