#include "opUndo.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


//Add Rectangle operation class
opUndo::opUndo(controller * pCont):operation(pCont){

}
opUndo::~opUndo(){

}
//Add copy to the controller
void opUndo::Execute(){
 	GUI* pUI = pControl->GetUI();  
	pUI->PrintMessage("undo has been pressed");

    if (!UndoStack.empty()){
    UndoStack.front()->Undo();
    RedoStack.push_front(UndoStack.front());
    UndoStack.pop_front();
    }


}