#pragma once
#include "..\controller.h"



class opLoad: public operation{
public:
	opLoad(controller *pCont);
	virtual ~opLoad();
	
	//Add Load to the controller
	virtual void Execute() ;
	virtual void Undo() ;
	virtual void Redo() ;


};