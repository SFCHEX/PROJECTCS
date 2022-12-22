#include "operation.h"
#include "opLoad.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <string>



opLoad::opLoad(controller *pCont):operation(pCont)
{ UndoStack.push(this);	}

opLoad::~opLoad(){
}

void opLoad::Execute() {
 	GUI* pUI = pControl->GetUI();  
	Graph* pGr = pControl->getGraph();
	pUI->PrintMessage("Enter the name of the file you would like to load from: ");
	string file=pUI->GetString();
    ifstream myfile;

    myfile.open(file+".txt");
	if (myfile.good()){pGr->Load(myfile,pUI);}

}




