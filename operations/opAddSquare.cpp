#include "opAddSquare.h"
#include "..\shapes\Square.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddSquare::opAddSquare(controller* pCont) :operation(pCont)
{ UndoStack.push_front(this);cleanRedo();	}
opAddSquare::~opAddSquare()
{
if(isUndone){
	Graph* pGr = pControl->getGraph();
	pGr->deletedShapeCleanUp(1);
}
}
void opAddSquare::Undo() {
isUndone=1;	
	Graph* pGr = pControl->getGraph();
	pGr->popShape();
}
void opAddSquare::Redo() {
isUndone=0;	
	Graph* pGr = pControl->getGraph();
	pGr->unDelete();
}

//Execute the operation
void opAddSquare::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Square: Click at First Corner");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at second corner";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all Square parameters
	GfxInfo SquareGfxInfo;

	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pUI->getCrntDrawColor();
	SquareGfxInfo.FillClr = pUI->getCrntFillColor();
	SquareGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	SquareGfxInfo.isFilled = pUI->getFillStatus();	//default is not filled
	SquareGfxInfo.isSelected = false;	//defualt is not selected


	//Create a Squareangle with the above parameters
	Square* S = new Square(P1, P2, SquareGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the Squareangle to the list of shapes
	pGr->Addshape(S);

}
