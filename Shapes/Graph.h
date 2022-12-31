#pragma once
#include "Shapes.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

//forward decl
class GUI;	
//A class that is responsible on everything related to shapes
class Graph
{
private:
	vector <shape*> shapesList; //a container to hold all shapes	
	deque<shape*> deletedShapesList; //a container to hold all shapes	
	shape* selectedShape;	//pointer to the currently selected shape
	vector <shape*> clipboard;
	void SaveColorRGB(ofstream& outfile,color RGB);	//Saves Rgb values to to a file
	vector<string> Parameterize(string p);	//makes a line parameters

public:										
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	int clipboardSize();
	void Draw(GUI* pUI) const;			//Draw the graph (draw all shapes)
	void CutShape();
	shape* Getshape(int x, int y, bool) const; //Search for a shape given a point inside the shape
	void deselAll(int valId);
	void unDelete();
	void popShape();
	void Save(ofstream& outfile,GUI* pUI);	//Save all shapes to a file
	void deletedShapeCleanUp(int number);
	void Load(ifstream& inputfile,GUI* pUI);	//Load all shapes from a file
	int nSelected();
	void DeleteShape(int);
	void CopyShape();
	void clearClipboard();
	vector<shape*> getSelShape(); 
	void PasteShape(Point p1);
	void StickImageGR(GUI* pUI) const; //StickImage to the selected shape
	void SetImagesToShapes();
	void ScrambleShapes(GUI* pUI);
	void SendToBack();
};
