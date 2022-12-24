#include "operation.h"
#include "opDrag.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <string>


opDrag::opDrag(controller* pCont) :operation(pCont) 
{ UndoStack.push(this);	
}

opDrag::~opDrag() {
	GUI* pUI = pControl->GetUI();

}
void opDrag::Undo(){
		if (selshape[0]!=nullptr){
		for (int i = 0; i < selshape.size(); i++)
		selshape[i]->MoveShape(Point{previousPoints[i].x-finalPoints[i].x,previousPoints[i].y-finalPoints[i].y});
		}
	

}
void opDrag::Redo(){
		if (selshape[0]!=nullptr){
		for (int i = 0; i < selshape.size(); i++) {
			selshape[i]->MoveShape(Point{-previousPoints[i].x+finalPoints[i].x,-previousPoints[i].y+finalPoints[i].y});
			}	
		}
}
void opDrag::Execute() 
	{	
{
		GUI* pUI = pControl->GetUI();
		Graph* pGr = pControl->getGraph();
		selshape = pGr->getSelShape();
		Point point1;
		int tx = 0; int ty = 0;
		int ix = 0; int iy = 0;
		int nix = 0; int niy = 0;
		bool brk = 0; bool strt = 0;
		if (selshape[0] != nullptr) {

			for (int i=0; i<selshape.size();i++)
			previousPoints.push_back(selshape[i]->getPoints().s_Points[0]);

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
								pUI->CreateDrawToolBar();
								brk = 1;
							}
						}

					}

				}
				else {
					if (brk == 1) {
						break;
						pUI->ClearStatusBar();
					}
				}
			}
		for (int i=0; i<selshape.size();i++)
		finalPoints.push_back(selshape[i]->getPoints().s_Points[0]);
		}

		else {
			UndoStack.pop();
			pUI->PrintMessage("Please select one or more shapes first");
		}

	}


}