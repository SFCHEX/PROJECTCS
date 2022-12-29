#include "opAddOval.h"
#include "..\shapes\Oval.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddOval::opAddOval(controller* pCont) :operation(pCont)
{ UndoStack.push_front(this);cleanRedo();	}
opAddOval::~opAddOval()
{
	if(isUndone){
	Graph* pGr = pControl->getGraph();
	pGr->deletedShapeCleanUp(1);
	}
}
void opAddOval::Undo() {
	isUndone=1;
	Graph* pGr = pControl->getGraph();
	pGr->popShape();
}
void opAddOval::Redo() {
	isUndone=0;
	Graph* pGr = pControl->getGraph();
	pGr->unDelete();
}

//Execute the operation
void opAddOval::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Oval: Click at first corner");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at second corner";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all Oval parameters
	GfxInfo OvalGfxInfo;

	//get drawing, filling colors and pen width from the interface
	OvalGfxInfo.DrawClr = pUI->getCrntDrawColor();
	OvalGfxInfo.FillClr = pUI->getCrntFillColor();
	OvalGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	OvalGfxInfo.isFilled = pUI->getFillStatus();	//default is not filled
	OvalGfxInfo.isSelected = false;	//defualt is not selected


	//Create a Oval with the above parameters
	Oval* R = new Oval(P1, P2, OvalGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the Oval to the list of shapes
	pGr->Addshape(R);

}
