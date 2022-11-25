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
	//If a shape is found return a pointer to it.
	//if this point (x,y) does not belong to any shape return NULL


	///Add your code here to search for a shape given a point x,y	

	return nullptr;
}

//the save function will iterate through the shapeslist private vector and add it to the file
void Save(ofstream& outfile){

	//append shape and fill colors, endl
	outfile<<shapesList.size()<<endl;
	for (auto it = shapesList.begin(); it != shapesList.end(); ++it) {
		//append shapetype, tab
		//append shape ID, tab
		//loop for points
			//append each point, tab
		//another for loop for GfxInfo detail
			//add shape details to the file using the protected shape variables GfxInfo, tab
		//new lines
	}

	outputfile.close();

}
//the load function will open the file and iterate line by line through the file adding shapes to the shape vector. it will create shape objects based on the file
void load(ifstream& inputfile){
	string shapeText;
	while (getline(inputfile, shapeText)) {
		//break up string
		//create shape objects and append to shapelist
	}
	// Close the file
	inputfile.close(); 
}
