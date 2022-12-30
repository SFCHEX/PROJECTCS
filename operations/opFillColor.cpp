#include "opFillColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include <vector>

opFillColor::opFillColor(controller* pCount) :operation(pCount)
{ //UndoStack.push_front(this);cleanRedo();	
}

//void opFillColor::Undo(){
//	if (selShape!=nullptr){
//	if(noPrevColor)
//	selShape->noFillColor();
//	else
//	selShape->ChngFillClr(previousColor);
//	}
//}

//void opFillColor::Redo(){
//	if (selShape!=nullptr)
//	selShape->ChngFillClr(newColor);
//}



void opFillColor::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();
	vector<shape*> selectedShapes = pGr->getSelShape();
		
	if (selectedShapes.size())
	{
		pUI->GetColorFromColorPalette(newColor);
		for (int i = 0; i < selectedShapes.size(); i++)
		{
			selectedShapes[i]->ChngFillClr(newColor);
		}
	}

		
	/*if (selShape != nullptr)
	{
		if (selShape->getGfxInfo().isFilled){
			previousColor=selShape->getGfxInfo().FillClr;
			noPrevColor=false;
		}


		pUI->GetColorFromColorPalette(newColor);
		selShape->ChngFillClr(newColor);
	}*/
	else
	{
		//delete UndoStack.front();
		//UndoStack.front()=nullptr;
		//UndoStack.pop_front();
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