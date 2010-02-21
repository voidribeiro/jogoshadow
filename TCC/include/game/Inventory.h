#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "GameObject.h"
#include "TextureManager.h"
#include "ComponentModel.h"
#include "ComponentImage.h"
//#include "ComponentInteract.h"
#include <map>

using namespace irr;
using namespace gui;

class Inventory {
  private:
    std::map <std::string, GameObject*> items;
    std::map <std::string, IGUIElement*> inventoryButtons;
    struct SSelectedItem{
      std::string name;
      IGUIElement* element;
    } SelectedItem;

    core::rect<s32> rectAll;   //rect da janela toda
    ITexture* backgroundImage; //imagem de fundo
    bool lastVisible;
    bool isVisible;            //se o invent�rio est� vis�vel, caso verdadeiro deve mudar o input para o contexto 
                               //de invent�rio e n�o interagir na tela "atr�s"

    ComponentModel* getComponentModel(std::string objName);
    ComponentImage* getComponentImage(std::string objName);

  public:
    explicit Inventory();
    virtual ~Inventory();

    void add(GameObject* obj);                  //adiciona o �tem ao jogador
    void remove(const std::string objName);     //remove o �tem do jogador
    bool isInInventory(const std::string objName);

    void setBackground(const std::string filename);
    void setVisible(const bool visible);
    bool getVisible() {return isVisible;}
    void draw();

    void CreateInventoryButtons();
    void RemoveInventoryButtons();

    GameObject* getGameObject(std::string objName);

};

#endif