#pragma once
#include "rPoly.h"
#include "shape.h"
#include "math.h"
#include <vector>
#include <algorithm>
class rPoly : public shape
{
private:
	int num;
	Point P1;
	Point P2;
	vector<int> pVectX, pVectY;
public:
	rPoly(int, Point, Point, GfxInfo shapeGfxInfo);
	rPoly();
	virtual ~rPoly();
	double Convert(double degree);
	virtual void Draw(GUI* pUI) const;
	virtual shape* clone();	//select/unselect the shape
	virtual void Save(ofstream& outfile);	//Save all shapes to a file
	virtual bool isInside(int x, int y) const;
	virtual void Load(ifstream& inputfile);	//Load all shapes from a file
	virtual ShapePoints getPoints();
	virtual void MoveShape(Point pMove) override;	
	virtual void StickImageSh(GUI* pUI, string imagefile);
	virtual void resizeSH(double numb);
	virtual void rotateSH();
	virtual Point HideShape(Point) override;
	virtual void Zoom(double) override;
	void virtual scramble(Point)override;
};
