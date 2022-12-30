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
	pUI->PrintMessage("Resizing the selected shape(s), type your choice (1)by 2, (2)by 4, (3)by 1/2, (4)by 1/4");
	double num = 0;
	bool toggle;
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
				pUI->PrintMessage("Enter from 1 to 4, try again: ");
			}
		}
	} while (toggle);
	if (userinput == "1"){
		num = 2;
	}
	else if(userinput == "2"){
		num = 4;
	}
	else if(userinput =="3") {
		num = 0.5;
	}
	else if(userinput =="4") {
		num = 0.25;
	}
	pUI->ClearStatusBar();

	pGr->resizeGR(num);
}