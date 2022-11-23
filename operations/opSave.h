#pragma once
#include "operation.h"

class opSave: public operation{
public:
	opSave(controller *pCont);
	virtual ~opSave();
	
	//Add Load to the controller
	virtual void Execute() ;
	
};