#include "TextureManager.h"

TextureManager::TextureManager(){
}

std::map<std::string, video::ITexture*> TextureManager::textureMap;

TextureManager::~TextureManager(){
	for(std::map<std::string, video::ITexture*>::const_iterator it = textureMap.begin(); it != textureMap.end(); ++it){
		if (it->second != NULL){
      DeviceManager::GetDriver()->removeTexture(it->second);
		}
	}
}

video::ITexture* TextureManager::GetTexture(std::string imagePath){
	if (textureMap[imagePath] == NULL){
    textureMap[imagePath] = DeviceManager::GetDriver()->getTexture(imagePath.c_str());
	}
	return textureMap[imagePath];
}

void TextureManager::RemoveTexture(std::string imagePath){
	if (textureMap[imagePath] != NULL){
		DeviceManager::GetDriver()->removeTexture(textureMap[imagePath]);
		//TODO - Not removing the reference from the map. But the image is removed;
		textureMap[imagePath] = NULL;
	}
}