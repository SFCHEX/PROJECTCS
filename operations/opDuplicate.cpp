#include "opDuplicate.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opDuplicate::opDuplicate(controller* pCount) : operation(pCount)
{}

void opDuplicate::Execute()
{
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	pGr->DuplicateShapes();
	pUI->PrintMessage("Invoked");

}

opDuplicate::~opDuplicate()
{

}
