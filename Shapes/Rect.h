#pragma once

#include "shape.h"
#include "math.h"

class Rect : public shape
{
private:
	Point Corner1;	
	Point Corner2;
public:
	Rect(Point , Point, GfxInfo shapeGfxInfo );
	virtual ~Rect();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream& outfile);	//Save all shapes to a file
	virtual shape* clone();	//select/unselect the shape
	virtual bool isInside(int x, int y) const;
	//virtual void Load(ifstream& inputfile);	//Load all shapes from a file
	virtual ShapePoints getPoints(); //first elem is p1 sec is p2
	virtual void MoveShape(Point pMove) override;	
	virtual void StickImageSh(GUI* pUI, string imagefile);
	//virtual void scramble() override;
	virtual void resizeSH(double num);
	virtual void rotateSH();
	virtual void HideShape(Point) override;
};

