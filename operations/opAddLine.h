#pragma once
#include "operation.h"

class opAddLine : public operation
{
public:
	opAddLine(controller* pCont);
	virtual ~opAddLine();

	virtual void Execute();
	virtual void Undo() ;
	virtual void Redo() ;


};