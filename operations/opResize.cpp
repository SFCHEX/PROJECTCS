#include "opResize.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opResize::opResize(controller * pCont):operation(pCont){}

opResize::~opResize(){}

void opResize::Execute(){
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("Resizing the selected shape(s)");
	int num;
	bool toggle;
	string userinput;
	toggle = true;
	do {
		toggle = false;
		userinput = pUI->GetString();
		for (int i = 0; i < userinput.size(); i++) {
			if (!isdigit(userinput[i])) {
				toggle = true;
				pUI->PrintMessage("Your entered a character, try again: ");
			}
		}
	} while (toggle);
	num = stoi(userinput);
	pUI->ClearStatusBar();

	pGR->resizeGR(num);
}