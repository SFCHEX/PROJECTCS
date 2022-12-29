#pragma once
#include "operation.h"
#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"
#include <vector>

class opDeleteShape : public operation{
int nSel;
vector<shape*> deletedShapes;
public:
  opDeleteShape(controller *pCont);
  virtual ~opDeleteShape();
  virtual void Execute();
	virtual void Undo() ;
	virtual void Redo() ;


};
