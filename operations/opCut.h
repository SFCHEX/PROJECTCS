#pragma once
#include "operation.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


class opCut : public operation{
public:
  opCut(controller *pCont);
  virtual ~opCut();
  virtual void Execute();
};
