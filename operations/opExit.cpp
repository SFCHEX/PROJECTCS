#include "operation.h"
#include "opExit.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Graph.h"
#include <string>



    opExit::opExit(controller *pCont):operation(pCont){

    }	
    opExit::~opExit(){

    }
	
	//Add exit to the controller
	void opExit::Execute(){
              	GUI* pUI = pControl->GetUI();  
	            Graph* pGr = pControl->getGraph();   
				pUI->PrintMessage("Would you like to save? [y]yes enter anything for no:");
				if (pUI->GetString()=="y"){
					pUI->PrintMessage("What would you like to save the drawing as? ");
					ofstream myfile;
					myfile.open(pUI->GetString()+".txt");
					pGr->Save(myfile,pUI);
					}


    }
	