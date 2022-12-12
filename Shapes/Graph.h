#pragma once
#include "Shapes.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

//forward decl
class GUI;	
//A class that is responsible on everything related to shapes
class Graph
{
private:
	vector <shape*> shapesList; //a container to hold all shapes	
	shape* selectedShape;	//pointer to the currently selected shape
	vector <shape*> clipboard;
	void SaveColorRGB(ofstream& outfile,color RGB);	//Saves Rgb values to to a file
	vector<string> Parameterize(string p);	//makes a line parameters

public:										
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	void Draw(GUI* pUI) const;			//Draw the graph (draw all shapes)
	void CutShape();
	shape* Getshape(int x, int y, bool) const; //Search for a shape given a point inside the shape
	void deselAll(int valId);
	void Save(ofstream& outfile,GUI* pUI);	//Save all shapes to a file
	void Load(ifstream& inputfile,GUI* pUI);	//Load all shapes from a file
	void DeleteShape();
//	void ChangeFillColor(); //Changes the fill color  
	void StickImageGR(GUI* pUI); //StickImage to the selected shape
	void CopyShape();
	void clearClipboard();
	void PasteShape(Point p1);
	void ChangeFillColor(); //Changes the fill color   
};
