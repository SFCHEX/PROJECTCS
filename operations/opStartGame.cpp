#include "opStartGame.h"
#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opStartGame::opStartGame(controller* pCont) :operation(pCont)
{
	
}
opStartGame::~opStartGame() {
}

void opStartGame::Execute() {
	Graph* pGr = pControl->getGraph();
	

}