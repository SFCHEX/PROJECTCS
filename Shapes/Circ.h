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
	virtual shape* clone();	//select/unselect the shape
	virtual void Save(ofstream &outfile);	//Save the shape parameters to the file
	virtual bool isInside(int x, int y) const;
	//virtual void Load(ifstream &infile) = 0;	//Load the shape parameters to the file
	virtual ShapePoints getPoints(); //first element is center, second is radius
	virtual void MoveShape(Point pMove) override;	
	virtual void StickImageSh(GUI* pUI, string imagefile);
	//virtual void scramble() override;

	virtual void resizeSH(double num);
	virtual string match();
};



