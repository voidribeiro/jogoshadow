#ifndef _SCRIPT_H_
#define _SCRIPT_H_

/*

Name: Script.h

Description:
  This is the script management class. It opens and processes LUA files and responds to the GameManager calls.
  This is an altered version, based on the Script Class created by Fabio Vinícius Binder on ACA2D.

*/

#include <string.h>

/*
 * LUA includes
 */
extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
};

class Script{
  private:
    
    /*
     * LUA core
     */
    lua_State* state;

  public:
    explicit Script();
    virtual ~Script();

    /*
     * Open and closes LUA script files
     */
	  int  startScript(char *filename);
	  void endScript  ();

    /*
     * Recover simple values processed by LUA
     */
	  int         getIntScript   (char *name);
    double      getDoubleScript(char *name);
	  bool        getBoolScript  (char *name);
	  const char *getStringScript(char *name);

    /*
     * Recover struct values processed by LUA
     */
	  void   openStruct        (char *name);
	  char  *getStringStruct   (char *name);
	  int    getIntStruct      (char *name);
	  double getDoubleStruct   (char *name);

    /*
     * Opens a structure inside an other structure
     */
	  void openSubStruct(char *name);

    
    /*
     * Closes a sub-structure
     */
	  void closeSubStruct();

    /*
     * Calls a LUA function
     */
    bool callFunction( char* name, int *args, int nArgs , int *res, int nRes);

  void registerFunction(lua_CFunction function);

	void addGlobalVar(char* name, char* value);
  //[Rafael]Modified global var to put pointer to classes
  void addGlobalUserVar(char* tname, void* udata);
};

#endif