#include "operation.h"
#include "opSelect.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include "..\Shapes\Shape.h"


opSelect::opSelect(controller* pCont) :operation(pCont)
{
	if(GetKeyState(VK_CONTROL) & 0x8000) //checks if ctrl is held down
	{
		MultiSelect = false;
	}
	else {
		MultiSelect = true;
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
		shape* SelectedShape = pGr->Getshape(P1->x, P1->y, MultiSelect);
		if (SelectedShape != nullptr) {
			if (MultiSelect) {
				pGr->deselAll(SelectedShape->getID());
			}
			GfxInfo SelectedGfxInfo = SelectedShape->getGfxInfo();
			SelectedShape->SetSelected(1);
			string msg = "Shape: " + SelectedGfxInfo.ShapeType;
			msg += " | Border Width: ";
			msg += to_string(SelectedGfxInfo.BorderWdth);
			pUI->PrintMessage(msg);
		}
		else {
			pUI->ClearStatusBar();
		}
	}
	else {//else user us trying to swap the selection mode
		pGr->deselAll(-1);
		MultiSelect = !MultiSelect;
		if (!MultiSelect){
			pUI->PrintMessage("Selection Mode: Multi-Select");
		}
		else {
			pUI->PrintMessage("Selection Mode: Single-Select");

		}
	}
}