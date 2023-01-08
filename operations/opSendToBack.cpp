#include "opSendToBack.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opSendToBack::opSendToBack(controller* pCont) :operation(pCont)
{

}


void opSendToBack::Execute()
{
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	pGr->SendToBack(pUI);
}

opSendToBack::~opSendToBack()
{

}