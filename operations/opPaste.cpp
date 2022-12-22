#include "opPaste.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


//Add Rectangle operation class
opPaste::opPaste(controller * pCont):operation(pCont)
{ UndoStack.push(this);	}
opPaste::~opPaste(){

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
	pUI->ClearStatusBar();

}