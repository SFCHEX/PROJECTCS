#pragma once
#include "operation.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

class opGroup:public operation{
public:
	opGroup(controller* pCont);
	virtual ~opGroup();
	virtual void Execute();
};