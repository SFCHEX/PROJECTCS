#pragma once

#include "operation.h"

//Add iPoly operation class
class opAddiPoly : public operation
{
public:
	opAddiPoly(controller* pCont);
	virtual ~opAddiPoly();

	//Add iPoly to the controller
	virtual void Execute();

};

