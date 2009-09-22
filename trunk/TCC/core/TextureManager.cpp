#include "TextureManager.h"

TextureManager::TextureManager(IVideoDriver* driver){
	this->driver = driver;
}

TextureManager::~TextureManager(){
	for(std::map<std::string, video::ITexture*>::const_iterator it = textureMap.begin(); it != textureMap.end(); ++it){
		if (it->second != NULL){
			driver->removeTexture(it->second);
		}
	}
}

video::ITexture* TextureManager::GetTexture(std::string imagePath){
	if (textureMap[imagePath] == NULL){
		textureMap[imagePath] = driver->getTexture(imagePath.c_str());
	}
	return textureMap[imagePath];
}

void TextureManager::RemoveTexture(std::string imagePath){
	if (textureMap[imagePath] != NULL){
		driver->removeTexture(textureMap[imagePath]);
		//TODO - Not removing the reference from the map. But the image is removed;
		textureMap[imagePath] = NULL;
	}
}