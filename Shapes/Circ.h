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
	Circ();
	virtual ~Circ();
	virtual void Draw(GUI* pUI) const;
	virtual shape* clone();	//select/unselect the shape
	virtual void Save(ofstream &outfile);	//Save the shape parameters to the file
	virtual bool isInside(int x, int y) const;
	virtual void Load(ifstream &infile);	//Load the shape parameters to the file
	virtual ShapePoints getPoints(); //first element is center, second is radius
	virtual void MoveShape(Point pMove) override;	
	virtual void StickImageSh(GUI* pUI, string imagefile);
	//virtual void scramble() override;
	virtual Point HideShape(Point DxDy) override;
	virtual void resizeSH(double num);
	virtual void Zoom(double) override;

};



