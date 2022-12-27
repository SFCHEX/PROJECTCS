#include "opAddLine.h"
#include "..\shapes\Line.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddLine::opAddLine(controller* pCont) : operation(pCont)
{ UndoStack.push_front(this);	}
opAddLine::~opAddLine()
{

	Graph* pGr = pControl->getGraph();
	pGr->deletedShapeCleanUp(1);
}
void opAddLine::Undo() {
	Graph* pGr = pControl->getGraph();
	pGr->popShape();
}
void opAddLine::Redo() {
	Graph* pGr = pControl->getGraph();
	pGr->unDelete();
}

void opAddLine::Execute() {
	Point p1, p2;
	
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Line: Click at first end");
	//Read 1st ebd and store in point P1
	pUI->GetPointClicked(p1.x, p1.y);

	string msg = "First end is at (" + to_string(p1.x) + ", " + to_string(p1.y) + " )";
	msg += " ... Click at second end";
	pUI->PrintMessage(msg);
	//Read 2nd end and store in point P2
	pUI->GetPointClicked(p2.x, p2.y);
	pUI->ClearStatusBar();


	GfxInfo LineGfxInfo;

	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pUI->getCrntDrawColor();
	LineGfxInfo.FillClr = pUI->getCrntFillColor();
	LineGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	LineGfxInfo.isFilled = pUI->getFillStatus();	//default is not filled
	LineGfxInfo.isSelected = false;	//defualt is not selected


	//Create a Line with the above parameters
	Line* L = new Line(p1, p2, LineGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the Line to the list of shapes
	pGr->Addshape(L);

}