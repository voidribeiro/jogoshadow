#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "GameObject.h"
#include <map>

class Inventory {
  private:
    std::map <std::string, GameObject*> items;

  public:
    explicit Inventory();
    virtual ~Inventory();

    void Add(std::string objName, GameObject* obj);     //adiciona o �tem ao jogador
    void Remove(std::string objName);                   //remove o �tem do jogador

    GameObject* getGameObject(std::string objName);

};

#endif