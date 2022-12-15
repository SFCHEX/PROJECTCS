#include "opFillColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opFillColor::opFillColor(controller* pCount) :operation(pCount)
{}

void opFillColor::Execute()
{
	color newColor;
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	shape* shape = pGr->getSeclectedShape();
	if (shape != nullptr)
	{
		pUI->GetColorFromColorPalette(newColor);
		shape->ChngFillClr(newColor);
	}
	else
	{
		string msg = "Select a shape first. If you want to change the general fill color, enter yes: ";
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