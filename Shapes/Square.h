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
	virtual void Save(ofstream& outfile);	//Save all shapes to a file
	virtual shape* clone();	//select/unselect the shape
	virtual bool isInside(int x, int y) const;
//	virtual void Load(ifstream& inputfile);	//Load all shapes from a file
	virtual ShapePoints getPoints(); //first elem is p1 sec is p2
	virtual void MoveShape(Point pMove) override;
	virtual void StickImageSh(GUI* pUI, string imagefile);
	//virtual void scramble() override;
	virtual void rotateSH();
	virtual void resizeSH(double n);
};



