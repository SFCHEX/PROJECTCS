#pragma once
#include "operation.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"



class opPenColor : public operation
{
color newColor;

color previousColor;

shape* selShape=nullptr;
public:
	opPenColor(controller* pCont);
	void Execute();
	~opPenColor();
	//virtual void Undo();
	//virtual void Redo();
};
