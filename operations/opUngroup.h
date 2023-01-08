#pragma once
#include "operation.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


class opUngroup : public operation {
public:
	opUngroup(controller* pCont);
	virtual ~opUngroup();
	virtual void Execute();
};
