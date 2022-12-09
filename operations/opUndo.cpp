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

}