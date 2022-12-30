#include "opPenColor.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opPenColor::opPenColor(controller* pCount) :operation(pCount)
{ //UndoStack.push_front(this);cleanRedo();
}

//void opPenColor::Undo(){
//	if (selShape!=nullptr)
//	selShape->ChngDrawClr(previousColor);
//}

//void opPenColor::Redo(){
//	if (selShape!=nullptr)
//	selShape->ChngDrawClr(newColor);
//}

void opPenColor::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	vector<shape*> selectedShapes = pGr->getSelShape();

	if (selectedShapes.size())
	{
		pUI->GetColorFromColorPalette(newColor);
		for (int i = 0; i < selectedShapes.size(); i++)
		{
			selectedShapes[i]->ChngDrawClr(newColor);
		}
	}

	//if (selShape != nullptr)
	//{
	//	previousColor=selShape->getGfxInfo().DrawClr;
	//	pUI->GetColorFromColorPalette(newColor);
	//	selShape->ChngDrawClr(newColor);
	//}
	else
	{
		//delete UndoStack.front();
		//UndoStack.front()=nullptr;
		//UndoStack.pop_front();
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