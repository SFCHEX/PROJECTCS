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
void Save(ofstream& outfile,GUI* pUI){
	//here we add the draw color fill color and pen width from the pointer to the gUI

	//outfile<<pUI->getCrntDrawColor()<<"\t"<<pUI->getCrntFillColor()<<"\t"<<pUI->getCrntPenWidth()<<endl;
	//number of shapes is length of vector
	outfile<<shapesList.size()<<endl;
	for (auto it = shapesList.begin(); it != shapesList.end(); ++it) {
		
		//append shapetype, tab
		outfile<<it->GetShapeType()<<"\t"
		//append shape ID, tab
		outfile<<it->ID<<"\t";
		//loop for points
			//append each point, tab

		//another for loop for GfxInfo detail
		//return draw color. not sure how to return as string
		//outfile<<it->GfxInfo.DrawClr<<"\t";
		//return fill color if there is fill color if there isnt return no fil
		if (it->GfxInfo.isFilled)
		{
			//outfile<<it->GfxInfo.FillClr;
		}
		else
		{
			outfile<<"NO_FILL";
		}
		outputfile<<"\t";

		outfile<<it->GfxInfo.BorderWdth<<endl;
			//add shape details to the file using the protected shape variables GfxInfo, tab
		//new lines
	}

	outputfile.close();

}
//the load function will open the file and iterate line by line through the file adding shapes to the shape vector. it will create shape objects based on the file
void load(ifstream& inputfile,GUI* pUI){
	string shapeText;
	while (getline(inputfile, shapeText)) {
		//break up string
		//create shape objects and append to shapelist
	}
	// Close the file
	inputfile.close(); 
}
