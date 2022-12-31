#include "opRotate.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opRotate::opRotate(controller * pCont):operation(pCont){}

opRotate::~opRotate(){}

void opRotate::Execute() {
  Graph* pGr = pControl->getGraph();
  GUI* pUI = pControl->GetUI();
  pGr->rotateGR();
  pUI->PrintMessage("Selected Shape Rotated");

}