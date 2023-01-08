#include "Graph.h"
#include "../GUI/GUI.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
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
		if(i>=28) i = i - (28 * i/28);	
		string imagefile = ImagesToStick[i];
		if (shapesList[i]->hasImage()) {
			shapesList[i]->StickImageSh(pUI, imagefile);
			shapesList[i]->setHasImage();
		}
	}
}

void Graph::SetImagesToShapes() {
	for (int i = 0; i < shapesList.size(); i++) {
		if(shapesList[i]->IsSelected()) shapesList[i]->setHasImage();

	}
}

void Graph::Draw(GUI* pUI) const
{	
	pUI->ClearDrawArea();
	for (int i = 0; i < shapesList.size(); i++)
		shapesList[i]->Draw(pUI);
	for (int i = 0; i < cardList.size(); i++)
		cardList[i]->Draw(pUI);

	StickImageGR(pUI);

}


void Graph::ScrambleShapes() {

	int shapeListSize;
	if (shapesList.size() % 2 == 0) {
		shapeListSize = shapesList.size();
	}
	else {
		shapeListSize = shapesList.size() + 1;
	}
	int noPartitionsRows, noPartitionsCols;
	for (int i = shapeListSize; i >= 2; i--) {
		if (shapeListSize % i == 0) {
			noPartitionsCols = i;
			noPartitionsRows = shapeListSize / i;
		}
	}

	int partitionWidth = 1380 / noPartitionsRows;
	int partitionHeight = 620 / noPartitionsCols;

	// Define the vector to hold the center points of the partitions
	vector<Point> centers;

	// Iterate through the partitions
	for (int i = 0; i < noPartitionsRows; i++) {
		for (int j = 0; j < noPartitionsCols; j++) {
			// Calculate the center point of the partition
			int x = (i * partitionWidth) + (partitionWidth / 2);
			int y = (j * partitionHeight) + (partitionHeight / 2);
			Point center = { x, y + 100 };
			// Create a pair of the center point and add it to the vector
			centers.push_back(center);
		}
	}
	std::random_shuffle(centers.begin(), centers.end());
	for (int i = 0; i < shapesList.size(); i++) {
		shapesList[i]->scramble(centers[i]);
	}

}


void Graph::SendToBack(GUI* pUI)
{
	for (int i = 0; i < shapesList.size(); i++)
	{
		if (shapesList[i]->IsSelected() && shapesList[i] != shapesList[0])
		{	
			
			shape* selectedShape = shapesList[i];
			vector<shape*>::iterator location = shapesList.begin() + i;
			shapesList.erase(shapesList.begin() + i);
			shapesList.insert(shapesList.begin(), selectedShape);
			if (!selectedShape->isaCard()) { break; }
			else {
				Draw(pUI);
				Sleep(1000);
				shapesList.insert(shapesList.end(), selectedShape);
				shapesList.erase(shapesList.begin());
				break;
			}
		}
	}
}

shape* Graph::Getshape(int x, int y, bool SingleSelect) const
{
	//If a shape is found return a pointer to it.
	///Add your code here to search for a shape given a point x,y
	bool EmptyArea = true;
	for (int i = shapesList.size() - 1; i != -1;  i--) {
		shape* selPointer = shapesList[i];
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
		if (shapetype=="Line"){
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
	
		else if (shapetype=="Triangle"){
			shape* newShape=new Tri();
			newShape->Load(inputfile);
			Addshape(newShape);
		}

    }
    inputfile.close();	

}
vector<shape*> Graph::getSelShape() {
	vector<shape*> selected;
	bool select_exists = 0;
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->IsSelected()) {
			selected.push_back(shapesList[i]);
			select_exists = 1;
		}
	}
	if (!select_exists){
		selected.push_back(nullptr);
		return selected;
	}
	else {
		return selected;
	}
}
void Graph::rotateGR(){
	for(int i=0; i<shapesList.size(); i++){
		if(shapesList[i]->IsSelected()) shapesList[i]->rotateSH();
	}
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

void Graph::HideGraph(GUI* pUI) {
	const int GraphX = 1380; //width
	const int GraphY = 750; //height
	int CardAmnt = shapesList.size() ;
	Point CardDim;
	GfxInfo shpGfxInfo;
	shpGfxInfo.BorderWdth = 10;
	shpGfxInfo.DrawClr = RED;
	shpGfxInfo.isFilled = true;
	shpGfxInfo.isHidden = true;
	CardDim.x = GraphX / (CardAmnt ) ;
	CardDim.y = GraphY / (CardAmnt ) ;
	int cursize = shapesList.size();
	for (int i = 0; i < cursize; i++) {
		if (!shapesList[i]->isShpHidden()) {
			Point P1 = shapesList[i]->HideShape(CardDim);
			Point P2 = (P1 + CardDim);
			Rect* newShape = new Rect(P1, P2, shpGfxInfo);
			newShape->sethideID(shapesList[i]->getGameID());
			shapesList.push_back(newShape);
		}
	}
}

void Graph::Zoom(double Zf) {
	for (int i = 0; i < shapesList.size(); i++)
		shapesList[i]->Zoom(Zf);

}
void Graph::DeleteCards() {
	int countcards = 1;
	deselAll(-1);
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->isaCard()) {
			shapesList[i]->SetSelected(true);
			countcards++;
		}
		this->DeleteShape(countcards);
	}
	for (int i = 0; i < shapesList.size(); i++) {
		if (shapesList[i]->isaCard()) {
			shapesList[i]->SetSelected(true);
			countcards++;
		}
		this->DeleteShape(countcards);
	}
	for (int i = 0; i < shapesList.size(); i++) {
		shapesList[i]->unHideAll();

	}
}

void Graph::duplicateShapes(GUI* pUI)
{
	int n = shapesList.size();
	
		for (int i = 0; i < n; i++)
		{

		shape* newShape = shapesList[i]->clone();
		shapesList.push_back(newShape);
		newShape->MoveShape(Point{ 50, 50 });

		}
		
		if (pUI->CurrentMode() == 1)
		{
			for (int i = n; i < shapesList.size(); i++)
			{
				shapesList[i]->setGameID(shapesList[i-n]->getGameID());
			}
		}

}

bool Graph::MyMatchedShapes()
{

		vector<shape*> selectedShapes = getSelShape();
		
			if (selectedShapes[0]->getCardID() == selectedShapes[1]->getCardID())
			{
				return 1;
			}
			else
			{
				return 0;
			
			}
	
}
