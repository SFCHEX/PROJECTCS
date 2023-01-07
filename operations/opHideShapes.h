#pragma once

#include "operation.h"

//Add Rectangle operation class
class opHideShapes : public operation
{
public:
	opHideShapes(controller* pCont);
	virtual ~opHideShapes();

	virtual void Execute();

};
