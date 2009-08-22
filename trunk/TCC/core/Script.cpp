#include "Script.h"

Script::Script(){
}

Script::~Script(){
}

int Script::startScript(char *filename){
  state = lua_open();

  luaopen_base(state);
  //luaopen_io(state);
  luaopen_string(state);
  luaopen_math(state);

  int status = luaL_loadfile(state, filename);

  if (status == 0)
    lua_pcall(state, 0, 0, 0);

  return status;
}

void Script::endScript(){
  lua_close(state);
}

/*
 * Recover simple values processed by LUA
 */

int Script::getIntScript(char *name){
  lua_getglobal(state, name);
  return (int)lua_tonumber(state, -1);
}

double Script::getDoubleScript(char *name){
  lua_getglobal(state, name);
  return (double)lua_tonumber(state, -1);
}

bool Script::getBoolScript(char *name){
  lua_getglobal(state, name);
  return lua_toboolean(state, -1);
}

const char * Script::getStringScript(char *name){
  lua_getglobal(state, name);
  return lua_tostring(state, -1);
}

/*
 * Recover struct values processed by LUA
 * The parameter name is the name of the structure to be searched
 */


void Script::openStruct(char *name){
  lua_getglobal(state, name); 
}

char* Script::getStringStruct(char *name){
  char aux[255];
  lua_pushstring(state, name);
  lua_gettable(state, -2);
  strcpy_s(aux, lua_tostring(state,-1)); 
  lua_pop(state,1);

  return aux;
}

int Script::getIntStruct(char *name){
  int aux;
  lua_pushstring(state, name);
  lua_gettable(state, -2);
  aux = (int)lua_tonumber(state,-1); 
  lua_pop(state,1);

  return aux;
}

double Script::getDoubleStruct(char *name){
  double aux;
  lua_pushstring(state, name);
  lua_gettable(state, -2);
  aux = (double)lua_tonumber(state,-1); 
  lua_pop(state,1);

  return aux;
}


/*
 * Opens a structure inside an other structure
 */
void Script::openSubStruct(char *name){
  lua_pushstring(state, name);
  lua_gettable(state, -2);
}

/*
 * Closes a sub-structure
 */
void Script::closeSubStruct(){
  lua_pop(state,1);
}

/*
 * Opens a structure inside an other structure
 */
void Script::callFunction(char* name, int *args, int nArgs , int *res, int nRes){
  
  /*
   * Searchs the function name
   */
	lua_getglobal(state, name);
  
  /*
   * Insert the arguments
   */
  for (int i = 0; i < nArgs; i++)
	  lua_pushnumber(state, args[i]);
  
  /*
   * call the function
   */
	lua_call(state, nArgs, nRes);
	
  /*
   * Recover results
   */
  for (int i = 0; i < nRes; i++)
	  res[i] = (int)lua_tonumber(state, -(nRes - i));

	lua_pop(state, 1);
}

void Script::registerFunction(lua_CFunction function){
  lua_pushcfunction(state, function);
  //Call register function to register the rest
  if (lua_pcall(state,0,0,0)) {
        fprintf(stderr,"%s\n",lua_tostring(state,-1));
  }
}

void Script::addGlobalVar(char* name, char* value){
	lua_pushfstring(state, value);
	lua_setglobal(state, name);
}