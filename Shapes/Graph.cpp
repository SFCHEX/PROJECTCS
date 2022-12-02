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
	outfile<<RGB.ucRed<<","<<RGB.ucGreen<<","<<RGB.ucBlue<<",";
}
void Graph::Draw(GUI* pUI) const
{
	pUI->ClearDrawArea();
	for (auto shapePointer : shapesList)
		shapePointer->Draw(pUI);
}


shape* Graph::Getshape(int x, int y) const
{
	//If a shape is found return a pointer to it.
	///Add your code here to search for a shape given a point x,y	
	for (auto& selPointer : shapesList) {
		if (selPointer->isInside(x, y)) {
			return selPointer;
		}
		else {	//if this point (x,y) does not belong to any shape return NULL
			selPointer->SetSelected(0);
		}
	}
	//if (t) {
		//auto &shpptr = (shapesList[c]);
		//return shpptr;
	//}
	//else {
	return nullptr;
	//}

}

void Graph::deselAll(int valId)
{
	int Shpid;
	for (auto* pshp : shapesList) {
		Shpid = pshp->getID();
		if (Shpid != valId) {
			pshp->SetSelected(0);
		}
		//else {
		//	pshp->SetSelected(1);
		//}
	}
}

//the save function will iterate through the shapeslist private vector and add it to the file
void Graph::Save(ofstream& outfile, GUI* pUI) {
	//here we add the draw color fill color and pen width from the pointer to the gUI
	Graph::SaveColorRGB(outfile,pUI->getCrntDrawColor());
	//saves draw and fill color as rgb values
	Graph::SaveColorRGB(outfile,pUI->getCrntFillColor());
	outfile<<","<<pUI->getCrntPenWidth()<<endl;
	//number of shapes is length of vector
	outfile<<Graph::shapesList.size()<<endl;
	for (auto& it : Graph::shapesList) {
		GfxInfo it_info = it->getGfxInfo();
		outfile<<it_info.ShapeType<<","<<it_info.ID<<",";
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
void Graph::Load(ifstream& inputfile, GUI* pUI)
{
	shapesList.clear();
	string shapeText;
	while (getline(inputfile, shapeText)) {
	//create shape objects and append to shapelist
    vector<string> parameters;
    string parameter="";
    for (int i =shapeText.size()-2; i>-1;i--){
   
    	if (shapeText[i]!=','){
        	parameter=shapeText[i]+parameter;
			        	
        	}
        else{
        	parameters.push_back(parameter);
            parameter="";
            }
    }
    parameters.push_back(parameter);

    int size=parameters.size();

    GfxInfo shpGfxInfo;
    shpGfxInfo.BorderWdth=stoi(parameters[0]);
    if (parameters[1]=="NO_FILL"){
        shpGfxInfo.isFilled=false;
        shpGfxInfo.DrawClr=color(parameters[2][0],parameters[3][0],parameters[4][0]);
    }
    else{
        shpGfxInfo.isFilled=true;
        shpGfxInfo.FillClr=color(parameters[1][0],parameters[2][0],parameters[3][0]);
        shpGfxInfo.DrawClr=color(parameters[4][0],parameters[5][0],parameters[6][0]);
    }

    vector<string> reverseParameters;
//    reverse(parameters.begin(), parameters.end());
    for (int i=size-1;i>-1;i--){
        reverseParameters.push_back(parameters[i]);
    }


	if (parameters[0]=="Square"){

	}
	else if (parameters[0]=="Oval")
	{
	}
	else if (parameters[0]=="Triangle")
	{
	}
	else if (parameters[0]=="Line")
	{
	}
	else if (parameters[0]=="Rectangle")
	{
	}
	else if (parameters[0]=="Circle")
	{

	}

	else if (parameters[0]=="Irregular Polygon")

	{

	}


	}
	inputfile.close(); 
}
