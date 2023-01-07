#include "opHideShapes.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opHideShapes::opHideShapes(controller* pCont) :operation(pCont)
{

}


void opHideShapes::Execute()
{
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("Graph Hidden");
	pGr->HideGraph(pUI);
	

}

opHideShapes::~opHideShapes()
{

}