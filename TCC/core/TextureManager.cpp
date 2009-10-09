#include "TextureManager.h"

TextureManager::TextureManager(){
}

TextureManager::~TextureManager(){
	for(std::map<std::string, video::ITexture*>::const_iterator it = textureMap.begin(); it != textureMap.end(); ++it){
		if (it->second != NULL){
      DeviceManager::getInstance()->getDriver()->removeTexture(it->second);
		}
	}
}

video::ITexture* TextureManager::GetTexture(std::string imagePath){
	if (textureMap[imagePath] == NULL){
    textureMap[imagePath] = DeviceManager::getInstance()->getDriver()->getTexture(imagePath.c_str());
	}
	return textureMap[imagePath];
}

void TextureManager::RemoveTexture(std::string imagePath){
	if (textureMap[imagePath] != NULL){
		DeviceManager::getInstance()->getDriver()->removeTexture(textureMap[imagePath]);
		//TODO - Not removing the reference from the map. But the image is removed;
		textureMap[imagePath] = NULL;
	}
}