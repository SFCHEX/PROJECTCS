#include "operation.h"

stack<operation*> operation::UndoStack;
stack<operation*> operation::RedoStack;