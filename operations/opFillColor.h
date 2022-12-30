#pragma once
#include "operation.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

class opFillColor : public operation
{
private:
bool noPrevColor;
color newColor;

color previousColor;

shape* selShape=nullptr;
public:
	opFillColor(controller* pCont);
	void Execute();
	~opFillColor();
//	virtual void Undo();
	//virtual void Redo();


};