#pragma once
#include "operation.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

class opDuplicate : public operation
{

public:
	opDuplicate(controller* pCont);
	void Execute();
	~opDuplicate();

};