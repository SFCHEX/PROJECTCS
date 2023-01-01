#include "opPaste.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


//Add Rectangle operation class
opPaste::opPaste(controller * pCont):operation(pCont)
{ UndoStack.push_front(this);cleanRedo();hasUndo=1;}
opPaste::~opPaste(){
	if(isUndone){
	Graph* pGr = pControl->getGraph();
	pGr->deletedShapeCleanUp(pastedShapesNumber);
	}
}

void opPaste::Undo() {
	isUndone=1;
	Graph* pGr = pControl->getGraph();
	for (int i=0; i<pastedShapesNumber;i++)
	pGr->popShape();
}
void opPaste::Redo() {
	isUndone=0;
	Graph* pGr = pControl->getGraph();
	for (int i=0; i<pastedShapesNumber;i++)
	pGr->unDelete();

}
//Add copy to the controller
void opPaste::Execute(){
	Point p1;
	GUI* pUI = pControl->GetUI();
	Graph* pGr= pControl->getGraph();

	pUI->PrintMessage("Click Where would you like to paste: ");
	//Read 1st ebd and store in point P1
	pUI->GetPointClicked(p1.x, p1.y);

    pGr->PasteShape(p1);
	pastedShapesNumber=pGr->clipboardSize();
	pUI->ClearStatusBar();

}