#include "opSwitchToPlay.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opSwitchToPlay::opSwitchToPlay(controller* pCont) :operation(pCont) {}

opSwitchToPlay::~opSwitchToPlay() {}

void opSwitchToPlay::Execute() {
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	if (pUI->CurrentMode() == 0) {

		pUI->PrintMessage("Would you like to save before you enter play mode? [y]yes [anything]no ");
		if (pUI->GetString() == "y" || pUI->GetString() == "Y") {
			pUI->PrintMessage("Enter file name to save? ");
			string file = pUI->GetString();
			ofstream myfile;
			myfile.open(file + ".txt");
			pGr->Save(myfile, pUI);
		}
		pUI->switchToPlay();
	}
	else {
		pUI->switchToDraw();
		pGr->DeleteCards();
	}
}
