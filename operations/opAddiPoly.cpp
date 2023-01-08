#include "opAddiPoly.h"

#include "..\shapes\iPoly.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddiPoly::opAddiPoly(controller* pCont) :operation(pCont)
{ UndoStack.push_front(this);cleanRedo();hasUndo=1;	}
opAddiPoly::~opAddiPoly()
{
	if (isUndone){
	Graph* pGr = pControl->getGraph();
	pGr->deletedShapeCleanUp(1);
	}
}
void opAddiPoly::Undo() {
	isUndone=1;
	Graph* pGr = pControl->getGraph();
	pGr->popShape();
}
void opAddiPoly::Redo() {
	isUndone=0;
	Graph* pGr = pControl->getGraph();
	pGr->unDelete();
}

//Execute the operation
void opAddiPoly::Execute()
{

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("New irreg Polygon: How many verticies? :");
	int num;
	bool toggle;
	string userinput;
	vector<int> PvectX;
	vector<int> PvectY;


	toggle = true;
	do {
		toggle = false;
		userinput = pUI->GetString();
		for (int i = 0; i < userinput.size(); i++) {
			if (!isdigit(userinput[i]) || (userinput[0] == '0' && userinput.size() == 1)) {
				toggle = true;
				pUI->PrintMessage("Your entered a character, try again: ");
			}
		}
	} while (toggle);
	
	num = stoi(userinput);


	pUI->ClearStatusBar();
	pUI->PrintMessage("Enter your " + to_string(num) + " verticies");



	for (int i = 0; i < (num); i++) {
		int tx, ty;
		pUI->GetPointClicked(tx, ty);
		PvectX.push_back(tx);
		PvectY.push_back(ty);
	}


	pUI->ClearStatusBar();

	//Preapre all iPolyangle parameters
	GfxInfo iPolyGfxInfo;

	//get drawing, filling colors and pen width from the interface
	iPolyGfxInfo.DrawClr = pUI->getCrntDrawColor();
	iPolyGfxInfo.FillClr = pUI->getCrntFillColor();
	iPolyGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	iPolyGfxInfo.isFilled = pUI->getFillStatus();	//default is not filled
	iPolyGfxInfo.isSelected = false;	//defualt is not selected


	//Create a iPolyangle with the above parameters
	iPoly* iP = new iPoly(PvectX, PvectY, iPolyGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the iPoly to the list of shapes
	pGr->Addshape(iP);

}
