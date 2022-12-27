#pragma once
#include "..\DEFS.h"
#include "..\GUI\GUI.h"
#include <deque>
class controller; //forward class declaration

//Base class for all possible operations
class operation
{
protected:
	controller* pControl;	//operations needs control to do their job
	static deque<operation*> RedoStack;
	static deque<operation*> UndoStack;
public:

	operation(controller* pCont);
	virtual ~operation() {}

	//Execute operation (code depends on operation type)
	virtual void Execute() = 0;

	//To undo this operation (code depends on operation type)
	virtual void Undo(){}
	//To redo this operation (code depends on operation type)
	virtual void Redo(){}

};