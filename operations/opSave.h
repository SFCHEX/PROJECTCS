#pragma once
#include "operation.h"

class opSave: public operation{
public:
	opSave(controller *pCont);
	virtual ~opSave();
	
	//Add Save to the controller
	virtual void Execute() ;
	
};