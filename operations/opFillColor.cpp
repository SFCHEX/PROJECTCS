#include "opFillColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opFillColor::opFillColor(controller* pCount) :operation(pCount)
{UndoStack.push(this);}

void opFillColor::Undo(){
	if(noPrevColor)
	selShape->noFillColor();
	else
	selShape->ChngFillClr(previousColor);
}

void opFillColor::Redo(){
	selShape->ChngFillClr(newColor);
}



void opFillColor::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	selShape = pGr->getSelectedShape();

	if (selShape != nullptr)
	{
		if (selShape->getGfxInfo().isFilled){
			previousColor=selShape->getGfxInfo().FillClr;
			noPrevColor=false;
		}


		pUI->GetColorFromColorPalette(newColor);
		selShape->ChngFillClr(newColor);
	}
	else
	{
		string msg = "Select a selShape first. If you want to change the general fill color, enter yes: ";
		pUI->PrintMessage(msg);
		string response = pUI->GetString();
		if (response == "yes")
		{
			pUI->ClearStatusBar();
			pUI->GetColorFromColorPalette(newColor);
			pUI->setFillStatus();
			pUI->setCrntFillColor(newColor);
		
		}
		else
		{
			pUI->ClearStatusBar();
		}
	}

}


opFillColor::~opFillColor()
{

}