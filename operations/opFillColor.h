#pragma once
#include "operation.h"
#include "opFillColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

class opFillColor : public operation
{
private:
vector<bool>noPrevColors;
color newColor;

vector<color> previousColors;

vector<shape*> selectedShapes;
public:
	opFillColor(controller* pCont);
	void Execute();
	~opFillColor();
	virtual void Undo();
	virtual void Redo();


};