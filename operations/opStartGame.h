#pragma once
#include "operation.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"


class opStartGame : public operation {

public:
	opStartGame(controller* pCont);
	virtual ~opStartGame();
	virtual void Execute();

};

