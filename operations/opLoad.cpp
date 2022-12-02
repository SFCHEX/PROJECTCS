#include "operation.h"
#include "opLoad.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <string>



opLoad::opLoad(controller *pCont):operation(pCont){
}

opLoad::~opLoad(){
}

void opLoad::Execute() {
 	GUI* pUI = pControl->GetUI();  
	Graph* pGr = pControl->getGraph();
	string file=pUI->GetString();
    ifstream myfile;
    myfile.open(file+".txt");
    pGr->Load(myfile,pUI);

}




