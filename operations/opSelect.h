#pragma once
#include "operation.h"
class opSelect : public operation {
private:
	static bool SingleSelect;

public:
	opSelect(controller* pCont);
	virtual ~opSelect();

	//Add Save to the controller
	virtual void Execute();


};