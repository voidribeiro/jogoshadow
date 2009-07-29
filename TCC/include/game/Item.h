#ifndef _ITEM_H_
#define _ITEM_H_

#include "string.h"

class Item{
private:
  int id;
  char* description;

public:
  explicit Item();
  explicit Item(int id, char* description);
  ~Item();

  static void view();

};

#endif