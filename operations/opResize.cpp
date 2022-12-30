#include "opResize.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opResize::opResize(controller * pCont):operation(pCont){}

opResize::~opResize(){}

void opResize::Execute(){
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	pGr->resizeShape();
  
}