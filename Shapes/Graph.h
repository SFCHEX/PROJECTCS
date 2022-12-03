#pragma once
#include "Shape.h"
#include "Oval.h"
#include "Rect.h"
#include "iPoly.h"
#include "rPoly.h"
#include "Line.h"
#include "Circ.h"
#include "Tri.h"
#include "Square.h"

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
	void SaveColorRGB(ofstream& outfile,color RGB);	//Saves Rgb values to to a file
public:										
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	void Draw(GUI* pUI) const;			//Draw the graph (draw all shapes)
	shape* Getshape(int x, int y) const; //Search for a shape given a point inside the shape
	void deselAll(int valId);
	void Save(ofstream& outfile,GUI* pUI);	//Save all shapes to a file
	void Load(ifstream& inputfile,GUI* pUI);	//Load all shapes from a file
	void DeleteShape();
	void ChangeFillColor(); //Changes the fill color   
};
