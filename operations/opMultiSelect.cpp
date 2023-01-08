#include "opMultiSelect.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opMultiSelect::opMultiSelect(controller* pCont) :operation(pCont) {}

opMultiSelect::~opMultiSelect() {}

void opMultiSelect::Execute() {
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("What do you want to multiselect by? 1-shape type 2-fill color 3-border color");
	bool toggle;
	int num;
	string userinput;
	toggle = true;
	do {
		toggle = false;
		userinput = pUI->GetString();
		for (int i = 0; i < userinput.size(); i++) {
			if (!isdigit(userinput[i])) {
				toggle = true;

				pUI->PrintMessage("Invalid, try again: ");
			}
			else if ((userinput != "1") && (userinput != "2") && (userinput != "3") && (userinput != "4")) {
				toggle = true;
				pUI->PrintMessage("Enter from 1 to 3, try again: ");
			}
		}
	} while (toggle);
	if (userinput == "1") {
		num = 1;
	}
	else if (userinput == "2") {
		num = 2;
	}
	else if (userinput == "3") {
		num = 3;
	}
	
	pUI->ClearStatusBar();
	pGr->multiSelect(num);
	

}