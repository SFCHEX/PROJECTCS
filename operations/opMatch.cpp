#include "opMatch.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
opMatch::opMatch(controller* pCount) :operation(pCount)
{}


void opMatch::Execute()
{
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	bool result = pGr->MyMatchedShapes();
	if (result)
	{
		pUI->PrintMessage("You selected two identical shapes. You earned three points.");
	}
	else
	{
		pUI->PrintMessage("Wrong match");

	}
}


opMatch::~opMatch()
{}