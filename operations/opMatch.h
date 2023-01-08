#pragma once
#include "operation.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

class opMatch : public operation
{
public:
	opMatch(controller* pCont);
	void Execute();
	~opMatch();
};