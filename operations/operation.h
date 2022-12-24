#pragma once
#include "..\DEFS.h"
#include "..\GUI\GUI.h"
#include <stack>
class controller; //forward class declaration

//Base class for all possible operations
class operation
{
protected:
	controller* pControl;	//operations needs control to do their job
	static stack<operation*> RedoStack;
	static stack<operation*> UndoStack;
public:

	operation(controller* pCont) { 
		pControl = pCont; }	//constructor
	virtual ~operation() {}

	//Execute operation (code depends on operation type)
	virtual void Execute() = 0;

	//To undo this operation (code depends on operation type)
	virtual void Undo() {}

	//To redo this operation (code depends on operation type)
	virtual void Redo() {}

};