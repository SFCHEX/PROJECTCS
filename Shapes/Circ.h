#pragma once

#include "shape.h"

class Circ : public shape
{
private:
	Point Center;
	Point PointR;
public:
	int rad;
	Circ(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Circ();
	virtual void Draw(GUI* pUI) const;
	//virtual void Save(ofstream &outfile) = 0;	//Save the shape parameters to the file
	//virtual void Load(ifstream &infile) = 0;	//Load the shape parameters to the file


};



