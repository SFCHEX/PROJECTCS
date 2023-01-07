#pragma once

#include "shape.h"
#include "math.h"
#include <vector>
#include <algorithm>
class iPoly : public shape
{
private:
	vector<int> pVectX, pVectY;
public:
	iPoly(vector<int>, vector<int>, GfxInfo shapeGfxInfo);
	iPoly();
	virtual ~iPoly();
	virtual void Draw(GUI* pUI) const;
	virtual shape* clone();	//select/unselect the shape
	virtual void Save(ofstream& outfile);	//Save all shapes to a file
	virtual bool isInside(int x, int y) const;
	virtual void Load(ifstream& inputfile);	//Load all shapes from a file
	virtual ShapePoints getPoints(); 
	virtual void MoveShape(Point pMove) override;
	virtual void resizeSH(double n);
	virtual void rotateSH();
	virtual Point HideShape(Point);
	virtual void Zoom(double) override;

};
