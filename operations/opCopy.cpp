#include "opCopy.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


//Add Rectangle operation class
opCopy::opCopy(controller * pCont):operation(pCont){

}
opCopy::~opCopy(){

}
//Add copy to the controller
void opCopy::Execute(){
	GUI* pUI = pControl->GetUI();
	Graph* pGr= pControl->getGraph();

    pGr->clearClipboard();
	pUI->PrintMessage("Click Where would you like to paste: ");
    pGr->CopyShape();



}


