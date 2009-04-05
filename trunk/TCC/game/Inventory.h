#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "Item.h"
#include "vector.h"

class Inventory{
private:
  vector <Item*> items;

public:
  explicit Inventory();
  ~Inventory();

  void add(Item* i);
  Item* combine( Item* item1, Item* item2 );
};

#endif