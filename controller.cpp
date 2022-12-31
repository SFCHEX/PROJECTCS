#include "controller.h"
#include "operations.h"
//Constructor
controller::controller()
{
	pGr = new Graph;
	pUI = new GUI;	//Create GUI object
}

//==================================================================================//
//								operations-Related Functions							//
//==================================================================================//
operationType controller::GetUseroperation() const
{
	//Ask the input to get the operation from the user.
	return pUI->GetUseroperation();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an operation and executes it
operation* controller::createOperation(operationType OpType)
{
	operation* pOp = nullptr;
	
	//According to operation Type, create the corresponding operation object
	switch (OpType)
	{
		case DRAW_RECT:
			pOp = new opAddRect(this);
			break;

		case STICK_IMAGE:
			pOp = new opStickImage(this);
			break;


		case DRAW_LINE:
			pOp = new opAddLine(this);
			break;

		case DRAW_TRI:
			pOp = new opAddTri(this);
			break;
		case DRAW_CIRC:
			pOp = new opAddCirc(this);
			break;
		case COPY:
			pOp = new opCopy(this);
			break;
		case PASTE:
			pOp = new opPaste(this);
			break;
		case DRAW_SQUARE:
			pOp = new opAddSquare(this);
				break;
		case DRAW_OVAL:
			pOp = new opAddOval(this);
			break;
		case DRAW_IPOLY:
			pOp = new opAddiPoly(this);
			break;
		case DRAW_RPOLY:
			pOp = new opAddrPoly(this);
			break;
		case DRAWING_AREA:
			pOp = new opSelect(this);
			break;
		case CHNG_FILL_CLR:
			pOp = new opFillColor(this);
			break;
		case CHNG_DRAW_CLR:
			pOp = new opPenColor(this);
			break;
		case CHNG_PEN_WIDTH:
			pOp = new opPenWidth(this);
			break;
		case DELETE_SHAPE:
			pOp = new opDeleteShape(this);
			break;
		case LOAD:
			///create load operation
			pOp = new opLoad(this);
			break;	
		
		case SAVE:
			pOp = new opSave(this); //create save operation 
			break;

		case DRAG_MODE:
			pOp = new opDrag(this);
			break;
		case TO_PLAY:
			pOp = new opSwitchToPlay(this);
			break;
		case UNDO:
			pOp = new opUndo(this);
			break;
	
		case REDO:
			pOp = new opRedo(this);
			break;
		
		case EXIT:
			///create Exitoperation here
			pOp = new opExit(this); 
			break;
		case SCRAMBLE:
			pOp = new opScramble(this);
			break;
		case SEND_TO_BACK:
			pOp = new opSendToBack(this);
			break;
		case STATUS:	//a click on the status bar ==> no operation
			break;

	}

	return pOp;
	
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all shapes on the user interface
void controller::UpdateInterface() const
{	
	pGr->Draw(pUI);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the UI
GUI *controller::GetUI() const
{	return pUI; }
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the Graph
Graph* controller::getGraph() const
{
	return pGr;
}



//Destructor
controller::~controller()
{
	delete pUI;
	delete pGr;
	
}



//==================================================================================//
//							Run function											//
//==================================================================================//
void controller::Run()
{
	operationType OpType;
	do
	{
		//1. Ask the GUI to read the required operation from the user
		OpType = GetUseroperation();

		//2. Create an operation coresspondingly
		operation* pOpr = createOperation(OpType);
		 
		//3. Execute the created operation
		if (pOpr)
		{
			pOpr->Execute();//Execute
		}

		//Update the interface
		UpdateInterface();

	} while (OpType != EXIT);

}
