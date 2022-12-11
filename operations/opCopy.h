#pragma once

#include "operation.h"

//Add Rectangle operation class
class opCopy: public operation
{
public:
	opCopy(controller *pCont);
	virtual ~opCopy();
	//Add copy to the controller
	virtual void Execute() ;
	
};


