#include "opPenColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opPenColor::opPenColor(controller* pCount) :operation(pCount)
{ UndoStack.push_front(this);cleanRedo();}

void opPenColor::Undo(){
	if (selectedShapes.size()){
		for (int i=0;i<selectedShapes.size();i++){
			selectedShapes[i]->ChngDrawClr(previousColors[i]);
		}
	}
}

void opPenColor::Redo(){
	if (selectedShapes.size()){
		for (int i=0;i<selectedShapes.size();i++)
			selectedShapes[i]->ChngDrawClr(newColor);
		}
}
void opPenColor::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	selectedShapes = pGr->getSelShape();

	if (selectedShapes[0] != nullptr)
	{
		for (int i=0;i<selectedShapes.size();i++){
			previousColors.push_back(selectedShapes[i]->getGfxInfo().DrawClr);
		}	
	
		pUI->GetColorFromColorPalette(newColor);
		for (int i = 0; i < selectedShapes.size(); i++)
		{
			selectedShapes[i]->ChngDrawClr(newColor);
		}
	}


	else
	{
		delete UndoStack.front();
		UndoStack.front()=nullptr;
		UndoStack.pop_front();
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