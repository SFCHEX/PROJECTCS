#pragma once

#include "operation.h"

//Add Rectangle operation class
class opRedo: public operation
{
public:
	opRedo(controller *pCont);
	virtual ~opRedo();
	//Add copy to the controller
	virtual void Execute() ;
};