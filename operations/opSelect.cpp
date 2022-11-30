#include "operation.h"
#include "opSelect.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include "..\Shapes\Shape.h"

opSelect::opSelect(controller* pCont) :operation(pCont)
{
}

opSelect::~opSelect() {
}

void opSelect::Execute() {
	int x, y;
	GUI* pUI = pControl->GetUI();
	pUI->GetPointClicked(x, y);
	Graph* pGr = pControl->getGraph();
	shape* SelectedShape = pGr->Getshape(x, y);
	if (SelectedShape != nullptr) {
		GfxInfo SelectedGfxInfo = SelectedShape->getGfxInfo();
		SelectedShape->SetSelected(1);
		pUI->PrintMessage("Current selected shape is " + SelectedGfxInfo.ShapeType);
	}
}