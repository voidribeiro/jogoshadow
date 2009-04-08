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

int Script::getIntScript(char *name)
{
  lua_getglobal(state, name);
  return (int)lua_tonumber(state, -1);
}

double Script::getDoubleScript(char *name)
{
  lua_getglobal(state, name);
  return (double)lua_tonumber(state, -1);
}

bool Script::getBoolScript(char *name)
{
  lua_getglobal(state, name);
  return lua_toboolean(state, -1);

}

const char * Script::getStringScript(char *name)
{
  lua_getglobal(state, name);
  return lua_tostring(state, -1);
}


//
//Função openStruct
//Objetivo: abre uma estrutura composta
//Parâmetros: state, estado do lua, filename, nome da estrutura
//
void Script::openStruct(char *name)
{
  lua_getglobal(state, name); 
}

//
//Funções get????Struct
//Objetivo: pegam valores de dentro de uma estrutura composta
//Parâmetros: state, estado do lua, name, nome do campo
//
char* Script::getStringStruct(char *name)
{
  char aux[255];
  lua_pushstring(state, name);
  lua_gettable(state, -2);
  strcpy_s(aux, lua_tostring(state,-1)); 
  lua_pop(state,1);

  return aux;
}

int Script::getIntStruct(char *name)
{
  int aux;
  lua_pushstring(state, name);
  lua_gettable(state, -2);
  aux = (int)lua_tonumber(state,-1); 
  lua_pop(state,1);

  return aux;
}

double Script::getDoubleStruct(char *name)
{
  double aux;
  lua_pushstring(state, name);
  lua_gettable(state, -2);
  aux = (double)lua_tonumber(state,-1); 
  lua_pop(state,1);

  return aux;
}

//
//Função openSubScript
//Objetivo: abre uma sub estrutura (estrutura dentro de estrutura)
//Parâmetros: state, estado do lua, name, nome da sub estrutura
//
void Script::openSubStruct(char *name)
{
  lua_pushstring(state, name);
  lua_gettable(state, -2);
}

//
//Função closeSubStruct
//Objetivo: finaliza sub estrutura
//Parâmetros: state, estado do lua
//
void Script::closeSubStruct()
{
  lua_pop(state,1);
}

//
//Função callFunction
//Objetivo: chama uma função do script
//Parâmetros: state, estado do lua
//
void Script::callFunction(char* name, int *args, int nArgs , int *res, int nRes)
{
  // Busca função
	lua_getglobal(state, name);

  // Insere argumentos
  for (int i = 0; i < nArgs; i++)
	  lua_pushnumber(state, args[i]);

  // Chama a função
	lua_call(state, nArgs, nRes);

	// Recupera os resultados
  for (int i = 0; i < nRes; i++)
	  res[i] = (int)lua_tonumber(state, -(nRes - i));

	lua_pop(state, 1);
}