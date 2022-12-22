#include "opRedo.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


//Add Rectangle operation class
opRedo::opRedo(controller * pCont):operation(pCont){

}
opRedo::~opRedo(){

}
//Add copy to the controller
void opRedo::Execute(){
    RedoStack.top()->Redo();
    UndoStack.push(RedoStack.top());
    RedoStack.pop();
}