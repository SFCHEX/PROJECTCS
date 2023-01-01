#include "opCut.h"
#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opCut::opCut(controller* pCont):operation(pCont) {}

opCut::~opCut(){}

void opCut::Execute() {
	Graph* pGr = pControl->getGraph();
	int nSel = pGr->nSelected();
	pGr->CutShape(nSel);
}