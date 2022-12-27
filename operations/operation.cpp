#include "operation.h"

deque<operation*> operation::UndoStack;
deque<operation*> operation::RedoStack;
operation::operation(controller* pCont){
		pControl = pCont;
		if (UndoStack.size()>=5)	{
		UndoStack.pop_back();
		}

		RedoStack.clear();
}