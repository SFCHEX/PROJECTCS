#pragma once
#include "operation.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


class opPenWidth : public operation
{
	vector<int> previousWidths;
	int newWidth;
	vector<shape*> selectedShapes;
public:
	opPenWidth(controller* pCont);
	virtual ~opPenWidth();

	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

};