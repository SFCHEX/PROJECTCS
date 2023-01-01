#pragma once
#include "operation.h"
#include "opResize.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


class opResize : public operation{
  double num;
public:
  opResize(controller *pCont);
  virtual ~opResize();
  virtual void Execute();

};
