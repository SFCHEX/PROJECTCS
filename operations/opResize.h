#pragma once
#include "operation.h"

class opResize : public operation{
public:
  opResize(controller *pCont);
  virtual ~opResize();
  virtual void Execute();

};
