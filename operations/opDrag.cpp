#include "operation.h"
#include "opDrag.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <string>



opDrag::opDrag(controller* pCont) :operation(pCont) {
}

opDrag::~opDrag() {
}

void opDrag::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();
	shape* selshape = pGr->getSelShape();
	Point point1;
	point1.x = 1; point1.y = 1;
	int i = 0;
	Point* p1 = pUI->GetPrevPoint();
	bool a = false;
	int ix = 0; int iy = 0;

	if (selshape != nullptr) {
		while (1)
		{
			buttonstate lButton = pUI->getClickState(ix, iy);
			if (lButton == BUTTON_DOWN) {
				selshape->ChngDrawClr(GREEN);
				selshape->SetSelected(false);
				point1.x = ix; point1.y = iy;
				selshape->MoveShape(point1);
				Sleep(50);
				pGr->Draw(pUI);
				a = true;
			}
			if (!selshape->isInside(ix, iy) && a == true) {
				break;
			}
			//else
			//	break;
				//pUI->PrintMessage(to_string(i));

			//pUI->GetPointClicked(a, b);
			//if (lButton != BUTTON_DOWN)
			//	break;
		}
	}
}