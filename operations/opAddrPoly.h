#pragma once

#include "operation.h"

//Add Rectangle operation class
class opAddrPoly : public operation
{
public:
	opAddrPoly(controller* pCont);
	virtual ~opAddrPoly();

	//Add rectangle to the controller
	virtual void Execute();
	virtual void Undo() ;
	virtual void Redo() ;

};	

