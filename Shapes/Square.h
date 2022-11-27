#pragma once
#include "Shape.h"
class Square: public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Square(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Square();
	virtual void Draw(GUI* pUI) const;
//	virtual void Save(ofstream& outfile);	//Save all shapes to a file
//	virtual void Load(ifstream& inputfile);	//Load all shapes from a file
};



