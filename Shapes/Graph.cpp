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
	Graph::SaveColorRGB(outfile,pUI->getCrntDrawColor());
	//saves draw and fill color as rgb values
	Graph::SaveColorRGB(outfile,pUI->getCrntFillColor());
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
//the load function will open the file and iterate line by line through the file adding shapes to the shape vector. it will create shape objects based on the file
void Graph::Load(ifstream& inputfile, GUI* pUI)
{
	shapesList.clear();
	string shapeText;
	while (getline(inputfile, shapeText)) {
	//create shape objects and append to shapelist
    vector<string> parameters; //creates a vector to contain the paramaeters for init the shape
    string parameter=""; // each string is a parameter
    for (int i =shapeText.size()-2; i>-1;i--){
   
    	if (shapeText[i]!=','){
        	parameter=shapeText[i]+parameter;//parameters added in reverse
			        	
        	}
        else{
        	parameters.push_back(parameter);
            parameter="";
            }
    }
    parameters.push_back(parameter);
	//parameter list is added in reverse because we initialize the gfx info first, and number of points is inconsistent per each possible vector so indexing from the start to the end would be more difficult

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
	//reversing the list again to normal so we can grab the points now that we have gfxinfo which is common for all shapes. it is easier to work this way for the points
	reverse(parameters.begin(),parameters.end());
	//stoi converts string to int
	if (parameters[0]=="Square" ||parameters[0]=="Oval"||parameters[0]=="Line"||parameters[0]=="Rectangle"||parameters[0]=="Circle"){
		//initiliaze points to be used to the building of the shape object and the adding to the shapeslist
		Point P1{stoi(parameters[2]),stoi(parameters[3])};
		Point P2{stoi(parameters[4]),stoi(parameters[5])};
			if (parameters[0]=="Line")
			{
				//Line *S=new Circ(P1, P2, shpGfxInfo);
			}
			else if (parameters[0]=="Rectangle")
			{
			//	Rect *S=new Circ(P1, P2, shpGfxInfo);
			}
			else if (parameters[0]=="Circle")
			{
				//Circ *S=new Circ(P1, P2, shpGfxInfo);
			}
			else if (parameters[0]=="Oval")
			{
				//Oval *S=new Circ(P1, P2, shpGfxInfo);
			}
	}

	else if (parameters[0]=="Triangle")
	{
		//initiliaze points to be used to the building of the shape object and the adding to the shapeslist
		Point P1{stoi(parameters[2]),stoi(parameters[3])};
		Point P2{stoi(parameters[4]),stoi(parameters[5])};
		Point P3{stoi(parameters[6]),stoi(parameters[7])};

				//Tri *S=new Tri(P1, P2,P3, shpGfxInfo);
	
	}
	else if (parameters[0]=="Irregular Polygon")
	{
		
		vector<int> pVectX, pVectY;
		int limit;
		if (parameters[parameters.size()-1]=="NO_FILL"){
			//7 is the number of NON coordinate related parameters in the case there is no fill color
			limit=parameters.size()-7;
		}
		else{
			//7 is the number of NON coordinate related parameters in the case there is a fill color
			limit=parameters.size()-10;
		}
		for (int i=2;i<limit;i++){
			//add coordinates to vector lists based on if it is odd or even
			if(i%2==0)
				pVectX.push_back(stoi(parameters[i]));
			else
				pVectY.push_back(stoi(parameters[i]));
		}

		//iPoly *S=new iPoly(P1, P2,P3, shpGfxInfo);
	}

//	Addshape(S);


	}
	inputfile.close(); 
}
