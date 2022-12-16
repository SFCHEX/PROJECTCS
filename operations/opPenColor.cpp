#include "opPenColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opPenColor::opPenColor(controller* pCount) :operation(pCount)
{}

void opPenColor::Execute()
{
	color newColor;
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	shape* shape = pGr->getSelectedShape();
	if (shape != nullptr)
	{
		pUI->GetColorFromColorPalette(newColor);
		shape->ChngDrawClr(newColor);
	}
	else
	{
		string msg = "Select a shape first. If you want to change the general pen color, enter yes: ";
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