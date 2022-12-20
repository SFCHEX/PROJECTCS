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
//						shapes Management Functions			       					//
//==================================================================================//
void Graph::CopyShape()
{
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->IsSelected()) {
			clipboard.push_back(shapesList[i]);
		}
	}

    deselAll(-1);
}
//void Graph::CutShape()
//{
//	for (int i = 0; i < shapesList.size(); i++) {
//		if (shapesList[i]->IsSelected()) {
//			clipboard.push_back(shapesList[i]);
//			shapesList.erase(shapesList.begin() + i);
//	
//		}
//	}
//    deselAll(-1);
//}
// 
   
void Graph::clearClipboard()	
{
	clipboard.clear();
}
void Graph::PasteShape(Point& p1)
{
	for (int i = 0; i < clipboard.size(); i++) {
		shape* newShape=clipboard[i]->clone();
		newShape->MoveShape(p1);
		shapesList.push_back(newShape);

	}
}
//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp)
{
	//Add a new shape to the shapes vector
	shapesList.push_back(pShp);	
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface

int Graph::nSelected() { //returns num of selected elements
	int num = 0;
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->IsSelected()) {
			num++;
		}
	}
	return num;
}

void Graph::DeleteShape(int n){
	do {
		for (int i = 0; i < shapesList.size(); i++) {
			if (shapesList[i]->IsSelected()) {
				delete shapesList[i];
				shapesList[i] = nullptr;
				shapesList.erase(shapesList.begin() + i);
			}
		}
		n--;
	} while (n > 0) ;
}

string ImagesToStick[] ={"images\\ImagesToStick\\green_1.jpg",
						"images\\ImagesToStick\\green_2.jpg",
						"images\\ImagesToStick\\green_3.jpg",
						"images\\ImagesToStick\\green_4.jpg",
						"images\\ImagesToStick\\green_5.jpg",
						"images\\ImagesToStick\\green_6.jpg",
						"images\\ImagesToStick\\green_7.jpg",
						"images\\ImagesToStick\\blue_1.jpg",
						"images\\ImagesToStick\\blue_2.jpg",
						"images\\ImagesToStick\\blue_3.jpg",
						"images\\ImagesToStick\\blue_4.jpg",
						"images\\ImagesToStick\\blue_5.jpg",
						"images\\ImagesToStick\\blue_6.jpg",
						"images\\ImagesToStick\\blue_7.jpg",
						"images\\ImagesToStick\\yellow_1.jpg",
						"images\\ImagesToStick\\yellow_2.jpg",
						"images\\ImagesToStick\\yellow_3.jpg",
						"images\\ImagesToStick\\yellow_4.jpg",
						"images\\ImagesToStick\\yellow_5.jpg",
						"images\\ImagesToStick\\yellow_6.jpg",
						"images\\ImagesToStick\\yellow_7.jpg",
						"images\\ImagesToStick\\red_1.jpg",
						"images\\ImagesToStick\\red_2.jpg",
						"images\\ImagesToStick\\red_3.jpg",
						"images\\ImagesToStick\\red_4.jpg",
						"images\\ImagesToStick\\red_5.jpg",
						"images\\ImagesToStick\\red_6.jpg",
						"images\\ImagesToStick\\red_7.jpg"
};


shape* Graph::getSelectedShape()
{
	shape* newShape = nullptr;
		for (int i = 0; i < shapesList.size(); i++)
		{
			if (shapesList[i]->IsSelected())
			{
				newShape = shapesList[i];
				break;
			}
			
		}
		if (newShape != nullptr)
		{
			return newShape;
		}
		delete newShape;
		newShape = nullptr;
	}
	
void Graph::SaveColorRGB(ofstream& outfile,color RGB)	//Saves RGB values to to a file
{
	outfile<<(int)RGB.ucRed<<","<<(int)RGB.ucGreen<<","<<(int)RGB.ucBlue<<",";
}

void Graph::StickImageGR(GUI* pUI) const {
	for (int i = 0; i < shapesList.size(); i++) {
		string imagefile = ImagesToStick[i];
		if (shapesList[i]->hasImage()) {
			shapesList[i]->StickImageSh(pUI, imagefile);
			shapesList[i]->setHasImage();
		}
	}
}

void Graph::SetImagesToShapes() {
	for (int i = 0; i < shapesList.size(); i++) {
		shapesList[i]->setHasImage();
	}
}

void Graph::Draw(GUI* pUI) const
{
	pUI->ClearDrawArea();
	for (int i = 0; i < shapesList.size(); i++)
		shapesList[i]->Draw(pUI);
	StickImageGR(pUI);
}

shape* Graph::Getshape(int x, int y, bool SingleSelect) const
{
	//If a shape is found return a pointer to it.
	///Add your code here to search for a shape given a point x,y
	bool EmptyArea = true;
	for (auto& selPointer : shapesList) {
		if (selPointer->isInside(x, y)) {
			return selPointer;
			EmptyArea = false;
		}
		else {
			if (SingleSelect) {
				selPointer->SetSelected(0);
			}
			else{}
		}
	}
	if (EmptyArea) {
		for (auto& selPointer : shapesList) {
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
	color CFC=pUI->getCrntFillColor();
	color CDC=pUI->getCrntDrawColor();

	outfile<<(int)CFC.ucRed<<","<<(int)CFC.ucGreen<<","<<(int)CFC.ucBlue<<",";
	outfile<<(int)CDC.ucRed<<","<<(int)CDC.ucGreen<<","<<(int)CDC.ucBlue<<",";
	outfile<<pUI->getCrntPenWidth()<<endl;

	outfile<<shapesList.size()<<endl;

	for (auto& it : shapesList) {
		it->Save(outfile); //this virtual method adds special information that is exclusive to each individual shape to the file
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

shape* Graph::getSelShape() {
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->IsSelected()) {
			return shapesList[i];
		}
	}
	return nullptr;
}