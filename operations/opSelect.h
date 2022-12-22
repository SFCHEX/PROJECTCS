#pragma once
#include "operation.h"
#include <Windows.h>
class opSelect : public operation {
private:
	bool MultiSelect;

public:
	opSelect(controller* pCont);
	virtual ~opSelect();

	//Add Save to the controller
	virtual void Execute();

};