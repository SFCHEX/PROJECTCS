#include "opPenWidth.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opPenWidth::opPenWidth(controller* pCont) :operation(pCont)
{UndoStack.push(this);}

opPenWidth::~opPenWidth()
{}

void opPenWidth::Undo(){
		if (selShape!=nullptr)
		selShape->ChngPenWidth(previousWidth);
}

void opPenWidth::Redo(){
		if (selShape!=nullptr)
		selShape->ChngPenWidth(newWidth);
}


void opPenWidth::Execute()

{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	selShape = pGr->getSelectedShape();
	if (selShape != nullptr)
	{
		previousWidth=selShape->getGfxInfo().BorderWdth;
		pUI->PrintMessage("Enter a new width: ");
		newWidth = stoi(pUI->GetString());
		selShape->ChngPenWidth(newWidth);
		pUI->ClearStatusBar();

	}
	else
	{
		string msg = "Select a selShape first. If you want to change the general pen width, enter yes: ";
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