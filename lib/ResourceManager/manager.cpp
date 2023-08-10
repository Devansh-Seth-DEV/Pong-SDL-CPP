#include "manager.h"


ResourceManager::~ResourceManager() {
}

void ResourceManager::FreeResources() {
	std::unordered_map<std::string, TTF_Font*>::iterator it_font;
	while(it_font != m_fonts.end()){
		TTF_Font* font = it_font->second;
		TTF_CloseFont(font);
	}

	std::unordered_map<std::string, SDL_Surface*>::iterator it_surf;
	while(it_surf != m_surfaces.end()) {
		SDL_Surface* surface = it_surf->second;
		SDL_FreeSurface(surface);
	}
	std::cout << "all resources have been freed from memory" << std::endl;
}

void ResourceManager::FreeImgResources(std::string resource) {
	auto search = m_surfaces.find(resource);
	if(search != m_surfaces.end()) {
		SDL_FreeSurface(search->second);
		m_surfaces.erase(resource);
		std::cout << "Resource: " << resource << " [free]" << std::endl;
	} else {
		std::cout << "Resource: " << resource << " [already free]" << std::endl;
	}
}

void ResourceManager::FreeFontResources(std::string resource) {
	auto search = m_fonts.find(resource);
	if(search != m_fonts.end()) {
		TTF_CloseFont(search->second);
		m_fonts.erase(resource);
		std::cout << "Resource: " << resource << " [free]" << std::endl;
	} else {
		std::cout << "Resource: " << resource << " [already free]" << std::endl;
	}
}

ResourceManager* ResourceManager::GetInstance() {
	static ResourceManager* m_staticInstance = new ResourceManager;
	return m_staticInstance;
}

SDL_Surface* ResourceManager::GetImgSurface(std::string sourcePath) {
	auto search = m_surfaces.find(sourcePath);

	if(search != m_surfaces.end()) {
		std::cout << "resource exists: " << sourcePath << std::endl;
		return search->second;
	} else {
		SDL_Surface* surface = SDL_LoadBMP(sourcePath.c_str());
		if(surface == nullptr) {
			std::cerr << "BMP img load error: " << SDL_GetError() << std::endl;
			return nullptr;
		}
		m_surfaces.insert(std::make_pair(sourcePath, surface));
		std::cout << "resource added: " << sourcePath << std::endl;
		return surface; 
	}
}

TTF_Font* ResourceManager::GetFont(const char* fontFilePath, const int fontSize) {
	auto search = m_fonts.find(fontFilePath);

	if(search != m_fonts.end()) {
		std::cout << "resource exists: " << fontFilePath << std::endl;
		return search->second;
	} else {
		TTF_Font* font = TTF_OpenFont(fontFilePath, fontSize);
		if(font == nullptr) {
			std::cerr << "TTF font load error: " << TTF_GetError() << std::endl;
			return nullptr;
		}
		m_fonts.insert(std::make_pair(fontFilePath, font));
		std::cout << "resource added: " << fontFilePath << std::endl;
		return font;
	}
}

ResourceManager::ResourceManager()
{}

ResourceManager::ResourceManager(const ResourceManager& manager)
{}

ResourceManager ResourceManager::operator=(const ResourceManager& manager)
{
	return *this;
}
