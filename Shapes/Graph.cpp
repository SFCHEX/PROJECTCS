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

void Graph::SaveColorRGB(ofstream& outfile,color RGB)	//Saves Rgb values to to a file
{
	outfile<<RGB.ucRed<<"\t"<<RGB.ucGreen<<"\t"<<RGB.ucBlue<<"\t";
}
void Graph::Draw(GUI* pUI) const
{
	pUI->ClearDrawArea();
	for (auto shapePointer : shapesList)
		shapePointer->Draw(pUI);
}


shape* Graph::Getshape(int x, int y) const
{
	return nullptr;
	//for (auto& selPointer : shapesList) {
	//	if (1) {
	//		selPointer->
	//		//If a shape is found return a pointer to it.
	//		///Add your code here to search for a shape given a point x,y	
	//		//selPointer->
	//		//return selPointer;
	//	}
	//	else {
	//		//if this point (x,y) does not belong to any shape return NULL
	//		selPointer->SetSelected(0);
	//		return nullptr;
	//	}
	//}
}

//the save function will iterate through the shapeslist private vector and add it to the file
void Graph::Save(ofstream& outfile, GUI* pUI) {
	//here we add the draw color fill color and pen width from the pointer to the gUI
	Graph::SaveColorRGB(outfile,pUI->getCrntDrawColor());
	//saves draw and fill color as rgb values
	Graph::SaveColorRGB(outfile,pUI->getCrntFillColor());
	outfile<<"\t"<<pUI->getCrntPenWidth()<<endl;
	//number of shapes is length of vector
	outfile<<Graph::shapesList.size()<<endl;
	for (auto& it : Graph::shapesList) {
		GfxInfo it_info = it->getGfxInfo();
		outfile<<it_info.ShapeType<<"\t"<<it_info.ID<<"\t";
		it->Save(outfile); //this virtual method adds special information that is exclusive to each individual shape to the file
		Graph::SaveColorRGB(outfile,it_info.DrawClr);
		//if condition for if there is no fill color
		if (it_info.isFilled)
		{
			Graph::SaveColorRGB(outfile,it_info.FillClr);
		}
		else
		{
			outfile<<"NO_FILL";
		}		
		outfile<<it_info.BorderWdth<<endl;
	}
	outfile.close();
}
//the load function will open the file and iterate line by line through the file adding shapes to the shape vector. it will create shape objects based on the file
void Graph::Load(ifstream& inputfile, GUI* pUI) {}
//	string shapeText;
//	while (getline(inputfile, shapeText)) {
//		//break up string
//		//create shape objects and append to shapelist
//	}
//	// Close the file
//	inputfile.close(); 
//}
