#include "operation.h"

deque<operation*> operation::UndoStack;
deque<operation*> operation::RedoStack;
operation::operation(controller* pCont){
		pControl = pCont;
		if (UndoStack.size()>=5)	{
		delete UndoStack.back();
		UndoStack.back()=nullptr;
		UndoStack.pop_back();
		}

}

void operation::cleanRedo(){
	for(int i =0; i>RedoStack.size();i++){
		delete RedoStack.back();
		RedoStack.back()=nullptr;
		RedoStack.pop_back();
	}
}