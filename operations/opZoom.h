#pragma once

#include "operation.h"

//Add Rectangle operation class
class opZoom : public operation
{
public:
	opZoom(controller* pCont);
	virtual ~opZoom();

	virtual void Execute();

};
