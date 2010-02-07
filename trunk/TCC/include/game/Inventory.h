#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "GameObject.h"
#include "TextureManager.h"
#include "ComponentModel.h"
#include "ComponentImage.h"
#include <map>

class Inventory {
  private:
    std::map <std::string, GameObject*> items;

    core::rect<s32> rectAll;   //rect da janela toda
    ITexture* backgroundImage; //imagem de fundo
    bool isVisible;            //se o invent�rio est� vis�vel, caso verdadeiro deve mudar o input para o contexto 
                               //de invent�rio e n�o interagir na tela "atr�s"

    ComponentModel* getComponentModel(std::string objName);
    ComponentImage* getComponentImage(std::string objName);

  public:
    explicit Inventory();
    virtual ~Inventory();

    void add(std::string objName, GameObject* obj);     //adiciona o �tem ao jogador
    void remove(std::string objName);                   //remove o �tem do jogador

    void setBackground(std::string filename);
    void setVisible(bool visible);
    void draw();

    GameObject* getGameObject(std::string objName);

};

#endif