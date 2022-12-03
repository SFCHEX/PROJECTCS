#pragma once
#include "operation.h"
class opPenWidth : public operation
{
public:
	opPenWidth(controller* pCont);
	virtual ~opPenWidth();

	virtual void Execute();

};