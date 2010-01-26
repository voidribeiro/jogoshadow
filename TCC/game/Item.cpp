#include "Item.h"

Item::Item(){

}

Item::Item(string _name, string _description):name(_name){
  description[0] = _description;
}

Item::~Item(){
  if (node)
    node->remove();
  node = 0;

  if (mesh)
    mesh->drop();
	mesh = 0;
}