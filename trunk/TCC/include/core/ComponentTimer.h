#ifndef __COMPONENTTIMER_H__
#define __COMPONENTTIMER_H__

#include "AbstractComponent.h"
#include "DeviceManager.h"

#include "ScriptObject.h"

class ComponentTimer : public AbstractComponent{
  private:
    int timeOut;
    std::string scriptToExec;
    std::string functionToExec;
  public:
    explicit ComponentTimer(int _timeOut, std::string _script, std::string _function);
    virtual ~ComponentTimer();
    virtual void Update();
    virtual void Draw(){};
    int GetType() { return CTIMER; };
    const char* GetTypeName() { return "ComponentTimer"; };
};

class ComponentTimerBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
};

static const luaL_reg componentTimerFunctions[] = {
    {"Instantiate", ComponentTimerBinder::bnd_Instantiate},
    {"AddTo", ComponentTimerBinder::bnd_AddTo},
    {NULL, NULL}
};

#endif