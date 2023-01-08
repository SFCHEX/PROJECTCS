#pragma once
#include "operation.h"


#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


class opMultiSelect : public operation {
	
public:
	opMultiSelect(controller* pCont);
	virtual ~opMultiSelect();
	virtual void Execute();

};
