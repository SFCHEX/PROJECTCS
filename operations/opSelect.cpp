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
		pGr->deselAll(SelectedShape->getID());
		GfxInfo SelectedGfxInfo = SelectedShape->getGfxInfo();
		SelectedShape->SetSelected(1);
		string msg = "Shape: " + SelectedGfxInfo.ShapeType;
		msg += " Border Width: ";
		pUI->PrintMessage(msg);
	}
	else {
		pUI->ClearStatusBar();
	}
}