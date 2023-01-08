#include "opUngroup.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opUngroup::opUngroup(controller* pCont) :operation(pCont) {}

opUngroup::~opUngroup() {}

void opUngroup::Execute() {
	Graph* pGr = pControl->getGraph();
	pGr->ungroupShapes();

}