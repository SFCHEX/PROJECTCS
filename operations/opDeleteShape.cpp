#include "opDeleteShape.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opDeleteShape::opDeleteShape(controller *pCont):operation(pCont)
{ UndoStack.push(this);	}
opDeleteShape::~opDeleteShape(){}

void opDeleteShape::Execute(){
	Graph* pGr = pControl->getGraph();

	int nSel = pGr->nSelected();
		pGr->DeleteShape(nSel);
		GUI* pUI = pControl->GetUI();
		pUI->ClearStatusBar();
}
