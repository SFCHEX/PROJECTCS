#pragma once

#include "shape.h"
#include "math.h"

class Oval : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Oval(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Oval();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream& outfile);	//Save all shapes to a file
	virtual shape* clone();	//select/unselect the shape
	virtual bool isInside(int x, int y) const;
	//virtual void Load(ifstream& inputfile);	//Load all shapes from a file

};

