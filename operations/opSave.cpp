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
	string file=pUI->GetSrting();
    ofstream myfile;
    myfile.open(file+".txt");
    pGr->Save(myfile,pUI);

}