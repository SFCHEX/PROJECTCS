#include "operation.h"
#include "opSave.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <string>



opSave::opSave(controller *pCont):operation(pCont){
}

opSave::~opSave(){
}

void opSave::Execute() {
 	GUI* pUI = pControl->GetUI();  
	Graph* pGr = pControl->getGraph();
	pUI->PrintMessage("Enter the name of the file you would like to save to: ");
	string file=pUI->GetString();
    ofstream myfile;
    myfile.open(file+".txt");
    pGr->Save(myfile,pUI);
	pGr->isSaved=true;

}