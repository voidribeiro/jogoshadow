#ifndef __IMAGE2D_H__
#define __IMAGE2D_H__

#include <string>
#include "IDrawable.h"
#include "DeviceManager.h"
#include "TextureManager.h"

class Image2D:public IDrawable{
  private:
    std::string filename;
    TextureManager* textureManager;
    

  public:
    explicit Image2D(const std::string filename, TextureManager* textureManager);
    virtual ~Image2D();

    void draw();
    int getType(){return IMAGE;}

};

#endif