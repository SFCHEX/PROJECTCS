#include "Graph.h"
#include "../GUI/GUI.h"
Graph::Graph()
{
	selectedShape = nullptr;
}

Graph::~Graph()
{
}

//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//

//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp)
{
	//Add a new shape to the shapes vector
	shapesList.push_back(pShp);	
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface
void Graph::Draw(GUI* pUI) const
{
	pUI->ClearDrawArea();
	for (auto shapePointer : shapesList)
		shapePointer->Draw(pUI);
}


shape* Graph::Getshape(int x, int y) const
{
	return nullptr;
	//for (auto selPointer : shapesList) {
	//	if (1) {
	//		selPointer;
	//		//If a shape is found return a pointer to it.
	//		///Add your code here to search for a shape given a point x,y	
	//		selPointer->getBorders();
	//		return selPointer;
	//	}
	//	else {
	//		//if this point (x,y) does not belong to any shape return NULL
	//		selPointer->SetSelected(0);
	//		return nullptr;
	//	}
	//}
}
