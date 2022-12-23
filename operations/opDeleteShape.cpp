#include "opDeleteShape.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opDeleteShape::opDeleteShape(controller *pCont):operation(pCont)
{ UndoStack.push(this);	}
opDeleteShape::~opDeleteShape(){}


void opDeleteShape::Undo() {
	Graph* pGr = pControl->getGraph();

	GUI* pUI = pControl->GetUI();
	for (int i=0; i<nSel;i++)
	pGr->unDelete();
}
void opDeleteShape::Redo() {
	Graph* pGr = pControl->getGraph();
	for (int i=0; i<nSel;i++)
	pGr->popShape();

}


void opDeleteShape::Execute(){
	Graph* pGr = pControl->getGraph();

		nSel = pGr->nSelected();
		pGr->DeleteShape(nSel);
		GUI* pUI = pControl->GetUI();
		pUI->ClearStatusBar();
}
