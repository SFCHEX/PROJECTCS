#pragma once
#include "operation.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"



class opPenColor : public operation
{
vector<bool>noPrevColors;
color newColor;

vector<color> previousColors;

vector<shape*> selectedShapes;
public:
	opPenColor(controller* pCont);
	void Execute();
	~opPenColor();
	virtual void Undo();
	virtual void Redo();
};
