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
	vector<int> pVectX, pVectY;
public:
	rPoly(int, Point, Point, GfxInfo shapeGfxInfo);
	virtual ~rPoly();
	double Convert(double degree);
	virtual void Draw(GUI* pUI) const;
	virtual string GetShapeType() const;
	virtual void Save(ofstream& outfile);	//Save all shapes to a file
	virtual bool isInside(int x, int y) const;
	//virtual void Load(ifstream& inputfile);	//Load all shapes from a file
};
