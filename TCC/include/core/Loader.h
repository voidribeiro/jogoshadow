#ifndef _LOADER_H_
#define _LOADER_H_

extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
};

#include <string>
#include <list>

#include "ScriptObject.h"

using namespace std;

class Loader : public ScriptObject{
  private:
    std::string executablePath;

  public:
    explicit Loader(std::string appPath);
    virtual ~Loader();
    void LoadLevel(const char* level);
};

#endif