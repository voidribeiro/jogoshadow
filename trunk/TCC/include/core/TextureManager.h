#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include<irrlicht.h>

#include <map>
#include <string>

#include "DeviceManager.h"

using namespace std;
using namespace irr;
using namespace video;

class TextureManager{
	private:
		static std::map<std::string, video::ITexture*> textureMap;
    //static TextureManager instance;
	public:
		TextureManager();
		virtual ~TextureManager();
		static video::ITexture* GetTexture(std::string imagePath);
		static void RemoveTexture(std::string imagePath);
};

#endif