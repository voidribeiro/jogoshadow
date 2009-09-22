#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include<irrlicht.h>

#include <map>
#include <string>

using namespace std;
using namespace irr;
using namespace video;

class TextureManager{
	private:
		std::map<std::string, video::ITexture*> textureMap;
		IVideoDriver* driver;
	public:
		TextureManager(IVideoDriver* driver);
		virtual ~TextureManager();
		video::ITexture* GetTexture(std::string imagePath);
		void RemoveTexture(std::string imagePath);
};

#endif