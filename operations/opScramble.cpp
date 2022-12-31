#include "opScramble.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opScramble::opScramble(controller* pCont) :operation(pCont)
{

}


void opScramble::Execute()
{
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	pGr->ScrambleShapes(pUI);
	//pUI->PrintMessage("Function invoked");
}

opScramble::~opScramble()
{

}
