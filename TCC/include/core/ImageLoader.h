#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__

#include "TextureManager.h"

class ImageLoader{
  private:
    TextureManager* textureManager;
  public:
    explicit ImageLoader(TextureManager* textureManager);
    virtual ~ImageLoader();

};

#endif