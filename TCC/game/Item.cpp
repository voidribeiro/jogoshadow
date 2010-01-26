#include "Item.h"

Item::Item(){
}

Item::Item(string _name):name(_name){
}

Item::~Item(){
}

void Item::addDescription(const string description){
  descriptionList.push_back(description);
}

string Item::getDescription(const int idx){
  list<string>::iterator it;
  it = descriptionList.begin();

  if(descriptionList.size() < idx)
    it = descriptionList.end();
  else
    for(int i =0 ; i < idx; i++)
      it++;

  return (*it);
}