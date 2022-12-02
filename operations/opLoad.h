#pragma once
#include "operation.h"
#include "opLoad.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <string>



class opLoad: public operation{
public:
	opLoad(controller *pCont);
	virtual ~opLoad();
	
	//Add Load to the controller
	virtual void Execute() ;
	
};