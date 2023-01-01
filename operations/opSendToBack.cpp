#include "opSendToBack.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opSendToBack::opSendToBack(controller* pCont) :operation(pCont)
{

}


void opSendToBack::Execute()
{
	Graph* pGr = pControl->getGraph();
	pGr->SendToBack();
}

opSendToBack::~opSendToBack()
{

}