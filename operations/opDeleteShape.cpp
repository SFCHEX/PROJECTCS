#include "opDeleteShape.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opDeleteShape::opDeleteShape(controller *pCont):operation(pCont){}

opDeleteShape::~opDeleteShape(){}

Graph* pGr;
void opDeleteShape::Excute(){
		pGr->DeleteShape();
}
