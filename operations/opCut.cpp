#include "opCut.h"
#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opCut::opCut(controller* pCont):operation(pCont) 
{ UndoStack.push_front(this);cleanRedo();hasUndo=1;	}
opCut::~opCut(){
}

void opCut::Execute() {
	Graph* pGr = pControl->getGraph();
	pGr->clearClipboard();
	int nSel = pGr->nSelected();
	pGr->CutShape(nSel);
}