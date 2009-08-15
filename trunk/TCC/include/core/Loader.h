#ifndef __LOADER_H__
#define __LOADER_H__

#include <string>

#include "Script.h"

using namespace std;

class Loader{
  private:
    string executablePath;
    Script luaScript;

  public:
    Loader(string appPath);
    virtual ~Loader();
    void LoadLevel(char* level);
};

#endif