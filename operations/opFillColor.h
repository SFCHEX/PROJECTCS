#pragma once
#include "operation.h"


class opFillColor : public operation
{

public:
	opFillColor(controller* pCont);
	void Execute();
	~opFillColor();


};