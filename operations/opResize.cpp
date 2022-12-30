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
	pUI->PrintMessage("Resizing the selected shape(s), choose the scale factor: 1-two-times bigger 2-four-times bigger 3-two-times smaller 4-four-time smaller");
	//pGr->resizeShape();
  
}