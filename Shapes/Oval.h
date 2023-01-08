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
	Oval();
	virtual ~Oval();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream& outfile);	//Save all shapes to a file
	virtual shape* clone();	//select/unselect the shape
	virtual bool isInside(int x, int y) const;
	virtual ShapePoints getPoints(); //first elem is p1 sec is p2
	virtual void Load(ifstream& inputfile);	//Load all shapes from a file
	virtual void MoveShape(Point pMove) override;	
	virtual void StickImageSh(GUI* pUI, string imagefile);
	virtual void resizeSH(double num);
	virtual void rotateSH();
	virtual Point HideShape(Point) override;
	virtual void Zoom(double) override;
	void virtual scramble(Point)override;
};

