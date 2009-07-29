#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

// Standard ANSI-C includes
#include <stdio.h>

class StateManager{

  typedef struct State {
    void (*function)(void *ptr, long purpose);
    State *next;
    int stateType;

    State(){
      function  = NULL;
      next      = NULL;
      stateType = -1;
    }

    ~State(){  delete next; }

  } State;

  protected:
    State *parentState;

  public:
    StateManager();
    ~StateManager();

    void push(void (*function)( void *ptr, long purpose ), void *dataPtr = NULL);
    bool pop(void *dataPtr = NULL);
    void popAll(void *dataPtr = NULL);
    bool process(void *dataPtr = NULL);
};

#endif