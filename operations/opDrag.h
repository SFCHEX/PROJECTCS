#pragma once

#include "operation.h"

//Add Rectangle operation class
class opDrag : public operation
{
public:
	opDrag(controller* pCont);
	virtual ~opDrag();
	//Add copy to the controller
	virtual void Execute();

};
