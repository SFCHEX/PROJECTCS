#include "operation.h"
#include "opDrag.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <string>


opDrag::opDrag(controller* pCont) :operation(pCont) {
}

opDrag::~opDrag() {
	GUI* pUI = pControl->GetUI();
	pUI->CreateDrawToolBar();
	pUI->ClearStatusBar();
}
void opDrag::Undo(){
	if (count=0){
		for (int i = 0; i < selShapes.size(); i++) {
			Point movePointSub;
			movePointSub.x=-movePoint.x;
			movePointSub.y=-movePoint.y;
			selShapes[i]->MoveShape(movePointSub);
	
		}	

	}	
	count=1;

}
void opDrag::Redo(){
	if (count=1){
		for (int i = 0; i < selShapes.size(); i++) {
			selShapes[i]->MoveShape(movePoint);
		}	

	}	
	count=0;
}
void opDrag::Execute() 
	{	
{
		GUI* pUI = pControl->GetUI();
		Graph* pGr = pControl->getGraph();
		vector<shape*> selshape = pGr->getSelShape();
		Point point1;
		int tx = 0; int ty = 0;
		int ix = 0; int iy = 0;
		int nix = 0; int niy = 0;
		bool brk = 0; bool strt = 0;
		if (selshape[0] != nullptr) {
			pUI->PrintMessage("Start moving your shape(s) or click toolbar to quit without moving");
			for (int i = 0; i < 10; i) {
				if (pUI->getClickState(ix, iy) == BUTTON_DOWN) {
					while (brk == 0)
					{
						buttonstate lButton = pUI->getClickState(ix, iy);
						if (strt == 0) {
							tx = ix; ty = iy;
							strt = 1;
						}
						if (iy < 100 && strt == 0) { //toolbar hight
							brk = 1;
							pUI->ClearStatusBar();
						}
						else {
							nix = ix; niy = iy;
							point1.x = ix - tx; point1.y = iy - ty;
							tx = nix; ty = niy;
							for (int i = 0; i < selshape.size(); i++) {
								selshape[i]->MoveShape(point1);
								Sleep(2);
								pGr->Draw(pUI);
							}
							if (lButton == BUTTON_UP) {
								brk = 1;
							}
						}
					}
				}
				else {
					if (brk == 1) {
						break;
					}
				}
			}
		}
		else {
			pUI->PrintMessage("Please select one or more shapes first");
		}
	}
}