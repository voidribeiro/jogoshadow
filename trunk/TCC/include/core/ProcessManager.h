#ifndef _PROCESSMANAGER_H_
#define _PROCESSMANAGER_H_

// Standard ANSI-C includes
#include <stdio.h>

class ProcessManager{
  typedef struct Process{
    void (*function)(void *ptr, long purpose);
    Process *next;
    int processType;

    Process(){
      function = NULL;
      next = NULL;
      processType = -1;
    }

    ~Process(){
      delete next; 
      next = NULL;
    }

  } Process;

  protected:
    Process *parentProcess; 

  public:
    explicit ProcessManager();
    virtual ~ProcessManager();

    void push(void (*process)(void *ptr, long purpose), void *dataPtr = NULL);
    bool pop(void *dataPtr = NULL);
    void popAll(void *dataPtr = NULL);
    void process(void *ptr = NULL);
    void yeild();
};

#endif