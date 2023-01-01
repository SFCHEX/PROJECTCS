#pragma once
#include "operation.h"
#include "opResize.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


class opResize : public operation{
  double num;
  vector<double> previousScaleFactors;
  vector<shape*> selectedShapes;
public:
  opResize(controller *pCont);
  virtual ~opResize();
  virtual void Execute();
  virtual void Undo();
  virtual void Redo();

};
