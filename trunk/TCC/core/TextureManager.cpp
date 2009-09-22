#include "TextureManager.h"

TextureManager::TextureManager(IVideoDriver* driver){
	this->driver = driver;
}

TextureManager::~TextureManager(){
}

video::ITexture* TextureManager::GetTexture(std::string imagePath){
	return driver->getTexture(imagePath.c_str());
}

void TextureManager::RemoveTexture(std::string imagePath){
}