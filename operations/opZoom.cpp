#include "opZoom.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opZoom::opZoom(controller* pCont) :operation(pCont)
{

}


void opZoom::Execute()
{
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("Enter your zoom in factor (Decimals for zoom out, 0 for no zoom)");
	double num;
	bool toggle;
	string userinput;
	toggle = true;
	do {
		toggle = false;
		userinput = pUI->GetString();
		for (int i = 0; i < userinput.size(); i++) {
			if ((!isdigit(userinput[i]) || (userinput[0] == '0' && userinput.size() == 1)))
			{
				if (userinput[i] == '.' && userinput.size() > 1) 
				{
					continue;
				}
				else
				{
				toggle = true;
				pUI->PrintMessage("Your entered a character, try again: ");
				}
			}
		}
	} while (toggle);

	num = stod(userinput);
	pGr->Zoom(num);

}

opZoom::~opZoom()
{

}