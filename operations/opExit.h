#pragma once
#include "operation.h"

class opExit: public operation{
public:
	opExit(controller *pCont);
	virtual ~opExit();
	
	//Add Save to the controller
	virtual void Execute() ;
	
};