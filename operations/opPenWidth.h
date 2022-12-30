#pragma once
#include "operation.h"
#include "opPenWidth.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


class opPenWidth : public operation
{
	int previousWidth;
	int newWidth;
	shape* selShape=nullptr;
public:
	opPenWidth(controller* pCont);
	virtual ~opPenWidth();

	virtual void Execute();
//	virtual void Undo();
	//virtual void Redo();

};