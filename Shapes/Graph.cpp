#include "Graph.h"
#include "../GUI/GUI.h"
#include <iostream>
#include <cstdlib>
#include <vector>

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

int Graph::clipboardSize(){
	return clipboard.size();
}
void Graph::CopyShape()
{
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->IsSelected()) {
			clipboard.push_back(shapesList[i]);
		}
	}

    deselAll(-1);
	wasCut=0;
}
 
void Graph::clearClipboard()	
{
	if (wasCut){
	for (int i=0;i<clipboard.size();i++){
		delete clipboard[i];
		clipboard[i]=nullptr;
	}
	}
	clipboard.clear();
	
}
void Graph::PasteShape(Point p1)
{
	if (!clipboard.empty()){
	Point referencePoint=clipboard[0]->getPoints().s_Points[0];
	for (int i = 0; i < clipboard.size(); i++) {
		shape* newShape=clipboard[i]->clone();
		newShape->MoveShape(Point {(-referencePoint.x+p1.x),(-referencePoint.y+p1.y)} );
		newShape->SetSelected(0);
		shapesList.push_back(newShape);

	}
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
void Graph::popShape(){
	if (!shapesList.empty()){
	deletedShapesList.push_front(shapesList.back());
	shapesList.pop_back();
	}
}

void Graph::deletedShapeCleanUp(int number){
	for(int i=0;number>i;i++){
		delete deletedShapesList.back();
		deletedShapesList.back()=nullptr;
		deletedShapesList.pop_back();
	}
}
void Graph::unDelete(){
	shapesList.push_back(deletedShapesList.front());
	deletedShapesList.pop_front();
}

void Graph::DeleteShape(int n){
	do {
		for (int i = 0; i < shapesList.size(); i++) {
			if (shapesList[i]->IsSelected()) {
				deletedShapesList.push_front(shapesList[i]);
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
void Graph::ScrambleShapes(GUI* pUI) {
	srand(time(0));
	for (int i = 0; i < shapesList.size(); i++)
	{
		shapesList[i]->scramble(pUI);
	}
}


void Graph::SendToBack()
{
	for (int i = 0; i < shapesList.size(); i++)
	{
		if (shapesList[i]->IsSelected() && shapesList[i] != shapesList[0])
		{	
			shape* selectedShape = shapesList[i];
			shapesList.erase(shapesList.begin() + i);
			shapesList.insert(shapesList.begin(), selectedShape);
			break;
		}
	}
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

void Graph::resizeGR(double num){
	for(int i=0; i< shapesList.size(); i++){
		if(shapesList[i]->IsSelected()){
			shapesList[i]->resizeSH(num);
			
		}
	}
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

	outfile<<(int)CFC.ucRed<<" "<<(int)CFC.ucGreen<<" "<<(int)CFC.ucBlue<<" ";
	outfile<<(int)CDC.ucRed<<" "<<(int)CDC.ucGreen<<" "<<(int)CDC.ucBlue<<" ";
	outfile<<pUI->getCrntPenWidth()<<endl;

	outfile<<shapesList.size()<<endl;

	for (auto& it : shapesList) {
		it->Save(outfile); //this virtual method adds special information that is exclusive to each individual shape to the file
	}
	outfile.close();
}

//the load function will open the file and iterate line by line through the file adding shapes to the shape vector. it will create shape objects based on the file
void Graph::Load(ifstream& inputfile, GUI* pUI)
{
	for (int i=0;shapesList.size()>i;i++){
		delete shapesList[i];
		shapesList[i]=nullptr;
	}
	shapesList.clear();
	int red,green,blue,width,no_of_shapes;	
	inputfile>>red;inputfile>>green;inputfile>>blue;

	pUI->setCrntFillColor(color(red,green,blue));

	inputfile>>red;inputfile>>green;inputfile>>blue;

	pUI->setCrntDrawColor(color(red,green,blue));
	
	inputfile>>width;

	pUI->setCrntPenWidth(width);

	inputfile>>no_of_shapes;

    while (!inputfile.eof()) {
		string shapetype;
		inputfile>>shapetype;
		if (shapetype=="line"){
			shape* newShape=new Line();
			newShape->Load(inputfile);
			Addshape(newShape);
		}
		else if (shapetype=="Circle"){
			shape* newShape=new Circ();
			newShape->Load(inputfile);
			Addshape(newShape);
		}
		else if (shapetype=="iPoly"){
			shape* newShape=new iPoly();
			newShape->Load(inputfile);
			Addshape(newShape);
		}
		else if (shapetype=="Oval"){
			shape* newShape=new Oval();
			newShape->Load(inputfile);
			Addshape(newShape);
		}
		else if (shapetype=="Rect"){
			shape* newShape=new Rect();
			newShape->Load(inputfile);
			Addshape(newShape);
		}
		else if (shapetype=="rPoly"){
			shape* newShape=new rPoly();
			newShape->Load(inputfile);
			Addshape(newShape);
		}
		else if (shapetype=="Square"){
			shape* newShape=new Square();
			newShape->Load(inputfile);
			Addshape(newShape);
		}
	
		else if (shapetype=="Tri"){
			shape* newShape=new Tri();
			newShape->Load(inputfile);
			Addshape(newShape);
		}

    }
    inputfile.close();	

}
void Graph::CutShape(int nSel) {
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->IsSelected()) {
			clipboard.push_back(shapesList[i]);
			shapesList.erase(shapesList.begin() + i);
			i--;
		}
	}
	deselAll(-1);
	wasCut=1;

}