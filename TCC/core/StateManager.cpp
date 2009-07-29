#include "StateManager.h"

StateManager::StateManager(){ 
  parentState = NULL; 
}

StateManager::~StateManager(){
  popAll();
}

// push a function on to the stack
void StateManager::push(void (*function)(void *ptr, long purpose), void *dataPtr){
  State *statePtr;

  // Don't push a NULL value
  if(function != NULL) {
    // Allocate a new state and push it on stack
    statePtr = new State();

    statePtr->function = function;
    statePtr->next = parentState;

    parentState = statePtr;

    // Call state with init purpose
    statePtr->function(dataPtr, 0);
  }
}

bool StateManager::pop(void *dataPtr){
  State *statePtr;

  // Remove the head of stack (if any)
  if((statePtr = parentState) != NULL){
    // First call with shutdown purpose
    parentState->function(dataPtr, 2);

    parentState = statePtr->next;
    statePtr->next = NULL;
    delete statePtr;
  }

  // return true if more states exist, false otherwise
  if(parentState == NULL)
    return false;

  return true;
}

void StateManager::popAll(void *dataPtr){
  while(pop(dataPtr) == true);
}

bool StateManager::process(void *dataPtr){ 
  // return an error if no more states
  if(parentState == NULL)
    return false;

  // Process the top-most state
  parentState->function(dataPtr, 1); 

  return true;
}
