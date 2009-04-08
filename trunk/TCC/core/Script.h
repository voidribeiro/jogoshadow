#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string.h>

//Includes Lua
extern "C"{
	#include "../lua/lua.h"
	#include "../lua/lauxlib.h"
	#include "../lua/lualib.h"
};

class Script{
  private:
    lua_State* state;

  public:
    explicit Script();
    ~Script();

	  //Início e fim do script
	  int  startScript(char *filename);
	  void endScript  ();

	  //Pega valores simples do script
	  int         getIntScript   (char *name);
    double      getDoubleScript(char *name);
	  bool        getBoolScript  (char *name);
	  const char *getStringScript(char *name);

	  //Pega valores compostos do script
	  void   openStruct        (char *name);
	  char  *getStringStruct   (char *name);
	  int    getIntStruct      (char *name);
	  double getDoubleStruct   (char *name);
	  void   openSubStruct     (char *name);
	  void   closeSubStruct    ();

    // Chama função do lua
    void callFunction( char* name, int *args, int nArgs , int *res, int nRes);
};

#endif