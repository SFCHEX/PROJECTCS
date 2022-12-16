#include "opSwitchToPlay.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opSwitchToPlay::opSwitchToPlay(controller *pCont):operation(pCont){}

opSwitchToPlay::~opSwitchToPlay(){}

void opSwitchToPlay::Execute(){
		GUI* pUI = pControl->GetUI();
		pUI->DeleteShape();
}
