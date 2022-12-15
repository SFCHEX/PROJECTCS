#include "opPenWidth.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opPenWidth::opPenWidth(controller* pCont) :operation(pCont)
{}

opPenWidth::~opPenWidth()
{}

void opPenWidth::Execute()

{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	shape* shape = pGr->getSelectedShape();
	if (shape != nullptr)
	{
		pUI->PrintMessage("Enter a new width: ");
		int newWidth = stoi(pUI->GetString());
		shape->ChngPenWidth(newWidth);
		pUI->ClearStatusBar();

	}
	else
	{
		string msg = "Select a shape first. If you want to change the general pen width, enter yes: ";
		pUI->PrintMessage(msg);
		string response = pUI->GetString();
		if (response == "yes")
		{
			pUI->ClearStatusBar();
			pUI->PrintMessage("Enter a new width: ");
			int newWidth = stoi(pUI->GetString());
			pUI->ClearStatusBar();
			pUI->setCrntPenWidth(newWidth);

		}
		else
		{
			pUI->ClearStatusBar();
		}

	}

}