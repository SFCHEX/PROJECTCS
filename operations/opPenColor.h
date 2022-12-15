#pragma once
#include "operation.h"


class opPenColor : public operation
{

public:
	opPenColor(controller* pCont);
	void Execute();
	~opPenColor();

};
