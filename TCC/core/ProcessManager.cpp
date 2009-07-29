#include "ProcessManager.h"

ProcessManager::ProcessManager(){ 
  parentProcess = NULL; 
}

ProcessManager::~ProcessManager(){
  // pop each process
  while(pop()==true);
}

// Push a function on to the stack
void ProcessManager::push(void (*process)(void *ptr, long purpose), void *dataPtr){
  // Don't push a NULL value
  if(process != NULL){
    // Allocate a new process and push it on stack
    Process *processPtr = new Process();
    processPtr->function = process;
    processPtr->next = parentProcess;
    parentProcess = processPtr;

    // Call process with init purpose
    processPtr->function(dataPtr, 0);
  }
}

// pop top process from stack
bool ProcessManager::pop(void *dataPtr){
  Process *processPtr;

  // Remove the head of stack (if any)
  if((processPtr = parentProcess) != NULL){
    // First call with shutdown purpose
    parentProcess->function(dataPtr, 2);

    parentProcess = processPtr->next;
    processPtr->next = NULL;
    delete processPtr;
  }

  // return true if more processes exist, false otherwise
  if(parentProcess == NULL)
    return false;

  return true;
}

void ProcessManager::popAll(void *dataPtr){
  while(pop(dataPtr) == true);
}

// Process all functions
void ProcessManager::process(void *dataPtr){ 
  Process *processPtr = parentProcess;

  while(processPtr != NULL){
    processPtr->function(dataPtr, 1);
    processPtr = processPtr->next;
  }
}