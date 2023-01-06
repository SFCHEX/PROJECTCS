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
	virtual shape* clone();	//select/unselect the shape
	virtual bool isInside(int x, int y) const;
	double Area(int, int, int, int, int, int) const; // to calculate the area for triangles (subfunction of the isInside function)
//	virtual void Load(ifstream& inputfile);	//Load all shapes from a file
	virtual ShapePoints getPoints(); //first elem is p1 sec is p2 third is p3
	virtual void MoveShape(Point pMove) override;	
	virtual void StickImageSh(GUI* pUI, string imagefile);
	virtual void resizeSH(double n);
	virtual void rotateSH();
	virtual void HideShape(Point) override;
};

