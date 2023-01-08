#include "operation.h"
#include "opSelect.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include "..\Shapes\Shape.h"


opSelect::opSelect(controller* pCont) :operation(pCont)
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();
	if((GetKeyState(VK_CONTROL) & 0x8000) && pUI->CurrentMode() == 0) //checks if ctrl is held down
	{
		SingleSelect = false;
	}
	else {
		if (pUI->CurrentMode() == 0) {
			SingleSelect = true;
		}
		else {
			SingleSelect = false;
			if (pGr->nSelected() >= 2) {
				pGr->deselAll(-1);
				SingleSelect = true;
			}
		}
	}
}

opSelect::~opSelect() {
}

void opSelect::Execute() {

	Point* P1;
	GUI* pUI = pControl->GetUI();
	P1 = pUI->GetPrevPoint();
	Graph* pGr = pControl->getGraph();
	if (P1->y > 100){//checks if user selected a shape or pressed the selection mode button
		//if y bigger 100 then user is out of the bounds of taskbar so user selected a shape 
		shape* SelectedShape = pGr->Getshape(P1->x, P1->y, SingleSelect);
		if (SelectedShape != nullptr) {
			if (SingleSelect) {
				pGr->deselAll(SelectedShape->getID());
			}
			GfxInfo SelectedGfxInfo = SelectedShape->getGfxInfo();
			SelectedShape->SetSelected(1);
			if (SelectedShape->isaCard() && SingleSelect) {
				pGr->SendToBack(pUI);
			}
			if (pUI->CurrentMode() == 0) { //check if draw or play mode, no need to print data if its play mode
				string msg = "Shape: " + SelectedGfxInfo.ShapeType;
				msg += " | Border Width: ";
				msg += to_string(SelectedGfxInfo.BorderWdth);
				pUI->PrintMessage(msg);
			}
		}
		else {
			pUI->ClearStatusBar();
		}
	}
	else {//else user us trying to swap the selection mode
		pGr->deselAll(-1);

	}
}