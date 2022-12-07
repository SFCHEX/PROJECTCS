#include "Graph.h"
#include "../GUI/GUI.h"
#include <iostream>
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

void Graph::DeleteShape(){
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->IsSelected()) {
			shapesList.erase(shapesList.begin() + i);
		}
	}
}

void Graph::StickImage() {

}

//void Graph::ChangeFillColor(color)
//{
//	int count = 0;
//
//	
//	/*if (count == 0)
//	{
//		color NewColor = pColorPaletteForFillColor->GetNewColor();
//		for (int i = 0; i < shapesList.size(); i++)
//		{
//			color NewColor = pColorPaletteForFillColor->GetNewColor();
//			GfxInfo Info = shapesList[i]->getGfxInfo();
//			Info.FillClr = NewColor;
//		};
//	}*/
//	
//
//}
void Graph::SaveColorRGB(ofstream& outfile,color RGB)	//Saves Rgb values to to a file
{
	outfile<<(int)RGB.ucRed<<","<<(int)RGB.ucGreen<<","<<(int)RGB.ucBlue<<",";
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

	return nullptr;
}

void Graph::deselAll(int valId)
{
	int Shpid;
	for (auto* pshp : shapesList) {
		Shpid = pshp->getID();
		if (Shpid != valId) {
			pshp->SetSelected(0);
		}
	}
}

//the save function will iterate through the shapeslist private vector and add it to the file
void Graph::Save(ofstream& outfile, GUI* pUI) {
	//here we add the draw color fill color and pen width from the pointer to the gUI
	//saves draw and fill color as rgb values
	Graph::SaveColorRGB(outfile,pUI->getCrntFillColor());
	Graph::SaveColorRGB(outfile,pUI->getCrntDrawColor());
	outfile<<pUI->getCrntPenWidth()<<endl;
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
			outfile<<"NO_FILL"<<",";
		}		
		outfile<<it_info.BorderWdth<<endl;
	}
	outfile.close();
}

vector<string> Graph::Parameterize(string p){//returns string as parameters
    vector<string> parameters; //creates a vector to contain the paramaeters for init the shape
    string parameter=""; // each string is a parameter
   	for (int i =p.size()-1; i>-1;i--){
  
   	if (p[i]!=','){
       	parameter=p[i]+parameter;//parameters added in reverse
		        	
       	}
       else{
       	parameters.push_back(parameter);
           parameter="";
           }
   }
   parameters.push_back(parameter);
   return parameters;
}
//the load function will open the file and iterate line by line through the file adding shapes to the shape vector. it will create shape objects based on the file
void Graph::Load(ifstream& inputfile, GUI* pUI)
{
	shapesList.clear();
	string shapeText,drawToolsState,shapeCount;
	getline(inputfile,drawToolsState);
	
	vector<string> drawToolsParameters=Parameterize(drawToolsState);
	pUI->setCrntPenWidth(stoi(drawToolsParameters[0]));
	pUI->setCrntDrawColor(color (stoi(drawToolsParameters[3]),stoi(drawToolsParameters[2]),stoi(drawToolsParameters[1])));
//	pUI->setCrntFillColor(color (stoi(drawToolsParameters[6]),stoi(drawToolsParameters[5]),stoi(drawToolsParameters[4])));

	getline(inputfile,shapeCount);
	while (getline(inputfile, shapeText)) {
	vector<string> parameters=Parameterize(shapeText);
//parameter list is added in reverse because we initialize the gfx info first, and number of points is inconsistent per each possible vector so indexing from the start to the end would be more difficult

   	int size=parameters.size();

    GfxInfo shpGfxInfo;
    shpGfxInfo.BorderWdth=stoi(parameters[0]);
    shpGfxInfo.isSelected=false;
    if (parameters[1]=="NO_FILL"){
        shpGfxInfo.isFilled=false;
        shpGfxInfo.DrawClr=color(stoi(parameters[4]),stoi(parameters[3]),stoi(parameters[2]));
    }
    else{
        shpGfxInfo.isFilled=true;
        shpGfxInfo.FillClr=color(stoi(parameters[3]),stoi(parameters[2]),stoi(parameters[1]));
        shpGfxInfo.DrawClr=color(stoi(parameters[6]),stoi(parameters[5]),stoi(parameters[4]));
    }
	//reversing the list again to normal so we can grab the points now that we have gfxinfo which is common for all shapes. it is easier to work this way for the points
	reverse(parameters.begin(),parameters.end());
	//stoi converts string to int
	

	if (parameters[0]=="Square" ||parameters[0]=="Oval"||parameters[0]=="Line"||parameters[0]=="Rectangle"||parameters[0]=="Circle"){
		//initiliaze points to be used to the building of the shape object and the adding to the shapeslist
		Point P1{stoi(parameters[2]),stoi(parameters[3])};
		Point P2{stoi(parameters[4]),stoi(parameters[5])};
			if (parameters[0]=="Line")
			{
				Line *S=new Line(P1, P2, shpGfxInfo);
				Addshape(S);
			}
			else if (parameters[0]=="Rectangle")
			{
				Rect *S=new Rect(P1, P2, shpGfxInfo);
				Addshape(S);
			}
			else if (parameters[0]=="Circle")
			{
				Circ *S=new Circ(P1, P2, shpGfxInfo);
				Addshape(S);
			}
			else if (parameters[0]=="Oval")
			{
				Oval *S=new Oval(P1, P2, shpGfxInfo);
				Addshape(S);
			}
			else if (parameters[0]=="Square")
			{
				Square *S=new Square(P1, P2, shpGfxInfo);
				Addshape(S);
			}
	}

	else if (parameters[0]=="Triangle")
	{
		//initiliaze points to be used to the building of the shape object and the adding to the shapeslist
		Point P1{stoi(parameters[2]),stoi(parameters[3])};
		Point P2{stoi(parameters[4]),stoi(parameters[5])};
		Point P3{stoi(parameters[6]),stoi(parameters[7])};

				Tri *S=new Tri(P1, P2,P3, shpGfxInfo);
	
				Addshape(S);
	}
	else if (parameters[0]=="Irregular Polygon")
	{
		
		vector<int> pVectX, pVectY;
		int limit;
		if (parameters[parameters.size()-2]=="NO_FILL"){
			//5 is the number of NON coordinate related parameters in the case there is no fill color
			limit=parameters.size()-5;
		}
		else{
			//8 is the number of NON coordinate related parameters in the case there is a fill color
			limit=parameters.size()-7;
		}
		for (int i=2;i<limit;i++){
			//add coordinates to vector lists based on if it is odd or even
			if(i%2==0)
				pVectX.push_back(stoi(parameters[i]));
			else
				pVectY.push_back(stoi(parameters[i]));
		}

		iPoly *S=new iPoly(pVectX,pVectY, shpGfxInfo);
		Addshape(S);
	}
	else if (parameters[0]=="Regular Polygon")
	{
		Point P1{stoi(parameters[3]),stoi(parameters[4])};
		Point P2{stoi(parameters[5]),stoi(parameters[6])};
		
		rPoly *S=new rPoly(stoi(parameters[2]),P1,P2, shpGfxInfo);
		Addshape(S);
	}




	}
	inputfile.close(); 
}
