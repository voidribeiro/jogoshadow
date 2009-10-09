#ifndef __COMPONENTIMAGE_H__
#define __COMPONENTIMAGE_H__

#include "AbstractComponent.h"
#include "TextureManager.h"

//This class will substitute Image2D if is component driven
class ComponentImage : public AbstractComponent{
  private:
    std::string filename;
  public:
    explicit ComponentImage();
    virtual ~ComponentImage();
    
    virtual void Draw();
    int GetType() { return CIMAGE; };
};

#endif