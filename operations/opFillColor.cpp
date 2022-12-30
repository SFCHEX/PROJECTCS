#include "opFillColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
opFillColor::opFillColor(controller* pCount) :operation(pCount)
{UndoStack.push_front(this);cleanRedo();}

void opFillColor::Undo(){
	if (selectedShapes.size()){
	for (int i=0;i<selectedShapes.size();i++){
		if(noPrevColors[i])
			selectedShapes[i]->noFillColor();
		else
			selectedShapes[i]->ChngFillClr(previousColors[i]);
		}
	}
}

void opFillColor::Redo(){
	if (selectedShapes.size()){
	for (int i=0;i<selectedShapes.size();i++)
		selectedShapes[i]->ChngFillClr(newColor);
	}
}



void opFillColor::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();
	selectedShapes = pGr->getSelShape();


	if (selectedShapes.size())
	{
		for (int i=0;i<selectedShapes.size();i++){
			if(selectedShapes[i]->getGfxInfo().isFilled){
			previousColors.push_back(selectedShapes[i]->getGfxInfo().FillClr);
			noPrevColors.push_back(false);	
			}
			else
			{
				noPrevColors.push_back(true);	
			}
		}	
		pUI->GetColorFromColorPalette(newColor);
		for (int i = 0; i < selectedShapes.size(); i++)
		{
			selectedShapes[i]->ChngFillClr(newColor);
		}
	}

	else
	{
		delete UndoStack.front();
		UndoStack.front()=nullptr;
		UndoStack.pop_front();
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