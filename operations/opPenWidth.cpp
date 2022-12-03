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
	pUI->PrintMessage("Enter a new width: ");
	int newWidth = stoi(pUI->GetString());
	pUI->setCrntPenWidth(newWidth);
	pUI->ClearStatusBar();
}
