#pragma once

#include "operation.h"

//Add Rectangle operation class
class opPaste: public operation
{
	int pastedShapesNumber;
public:
	opPaste(controller *pCont);
	virtual ~opPaste();
	//Add copy to the controller
	virtual void Execute() ;
	virtual void Undo() ;
	virtual void Redo() ;


};