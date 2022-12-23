#include "opPenColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opPenColor::opPenColor(controller* pCount) :operation(pCount)
{UndoStack.push(this);}

void opPenColor::Undo(){
	selShape->ChngDrawClr(previousColor);
}

void opPenColor::Redo(){
	selShape->ChngDrawClr(newColor);
}

void opPenColor::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	selShape = pGr->getSelectedShape(); 

	if (selShape != nullptr)
	{
		previousColor=selShape->getGfxInfo().DrawClr;
		pUI->GetColorFromColorPalette(newColor);
		selShape->ChngDrawClr(newColor);
	}
	else
	{
		string msg = "Select a selShape first. If you want to change the general pen color, enter yes: ";
		pUI->PrintMessage(msg);
		string response = pUI->GetString();
		if (response == "yes")
		{
			pUI->ClearStatusBar();
			pUI->GetColorFromColorPalette(newColor);
			pUI->setCrntDrawColor(newColor);
		}
		else
		{
			pUI->ClearStatusBar();
		}
	
	}

}


opPenColor::~opPenColor()
{

}