#pragma once

#include "operation.h"

class opAddSquare : public operation
{
public:
	opAddSquare(controller* pCont);
	virtual ~opAddSquare();

	//Add Squareangle to the controller
	virtual void Execute();

};

