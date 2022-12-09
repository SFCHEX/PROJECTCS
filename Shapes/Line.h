#pragma once
#include "Shape.h"
class Line : public shape
{
private:
	Point End1;
	Point End2;
public:
	Line(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Line();

	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream &outfile);	//Save the shape parameters to the file
	virtual shape* clone();	//select/unselect the shape
	virtual bool isInside(int x, int y) const;
	//virtual void Load(ifstream &infile) = 0;	//Load the shape parameters to the file



};

