#include "opGroup.h"
#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opGroup::opGroup(controller* pCont) :operation(pCont)
{
	
}
opGroup::~opGroup() {
}

void opGroup::Execute() {
	Graph* pGr = pControl->getGraph();
	pGr->groupShapes();
	
}