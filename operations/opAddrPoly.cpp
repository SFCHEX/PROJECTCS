#include "opAddrPoly.h"
#include "..\shapes\rPoly.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opAddrPoly::opAddrPoly(controller* pCont) :operation(pCont)
{}
opAddrPoly::~opAddrPoly()
{}

//Execute the operation
void opAddrPoly::Execute()
{
	Point P1, P2;
	int num;
	bool toggle;
	string userinput;
	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("New rPoly; How many sides do you want:");
	toggle = true;
	do {
		toggle = false;
		userinput = pUI->GetString();
		for (int i = 0; i < userinput.size(); i++) {
			if (!isdigit(userinput[i])) {
				toggle = true;
				pUI->PrintMessage("Your entered a character, try again: ");
			}
		}
	} while (toggle);

	num = stoi(userinput);

	pUI->PrintMessage("Click at the center");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "The center is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at any point on the sides";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();

	//Preapre all rPolyle parameters
	GfxInfo rPolyGfxInfo;

	//get drawing, filling colors and pen width from the interface
	rPolyGfxInfo.DrawClr = pUI->getCrntDrawColor();
	rPolyGfxInfo.FillClr = pUI->getCrntFillColor();
	rPolyGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	rPolyGfxInfo.isFilled = false;	//default is not filled
	rPolyGfxInfo.isSelected = false;	//defualt is not selected


	//Create a rPolyle with the above parameters
	rPoly* C = new rPoly(num,P1, P2, rPolyGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the rPolyle to the list of shapes
	pGr->Addshape(C);

}
