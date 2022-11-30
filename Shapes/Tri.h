#pragma once

#include "shape.h"

class Tri : public shape
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
public:
	Tri(Point, Point,Point, GfxInfo shapeGfxInfo);
	virtual ~Tri();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream& outfile);	//Save all shapes to a file
	virtual bool isInside(int x, int y) const;
	double Area(int, int, int, int, int, int) const; // to calculate the area for triangles (subfunction of the isInside function)
//	virtual void Load(ifstream& inputfile);	//Load all shapes from a file
};

