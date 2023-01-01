#include "opPenWidth.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opPenWidth::opPenWidth(controller* pCont) :operation(pCont)
{ UndoStack.push_front(this);cleanRedo();hasUndo=1;}

opPenWidth::~opPenWidth()
{}

void opPenWidth::Undo(){
	if (selectedShapes.size()){
		for (int i=0;i<selectedShapes.size();i++){
			selectedShapes[i]->ChngPenWidth(previousWidths[i]);
		}
	}
}

void opPenWidth::Redo(){
	if (selectedShapes.size()){
		for (int i=0;i<selectedShapes.size();i++)
			selectedShapes[i]->ChngPenWidth(newWidth);
		}
}


void opPenWidth::Execute()

{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	selectedShapes = pGr->getSelShape();

	if (selectedShapes[0] != nullptr)
	{
		for (int i=0;i<selectedShapes.size();i++){
			previousWidths.push_back(selectedShapes[i]->getGfxInfo().BorderWdth);

		}	
	


		pUI->PrintMessage("Enter a new width: ");
		newWidth = stoi(pUI->GetString());

		for (int i = 0; i < selectedShapes.size(); i++)
		{
			selectedShapes[i]->ChngPenWidth(newWidth);
		}
		pUI->ClearStatusBar();
	}

	else
	{
		delete UndoStack.front();
		UndoStack.front()=nullptr;
		UndoStack.pop_front();
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