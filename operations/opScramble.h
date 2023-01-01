#pragma once
#include "operation.h"
#include "opScramble.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"



class opScramble : public opScramble
{
	
public:
	opScramble(controller* pCont);
	void Execute();
	~opScramble();

};
