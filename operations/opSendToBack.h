#pragma once
#include "operation.h"
#include "opScramble.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"



class opSendToBack : public operation
{

public:
	opSendToBack(controller* pCont);
	void Execute();
	~opSendToBack();

};
