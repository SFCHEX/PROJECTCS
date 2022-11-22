#pragma once

#include "shape.h"

class Circ : public shape
{
private:
	Point Center;
	Point PointR;
	int Radius = int(sqrt(pow((Center.x - PointR.x), 2) + pow((Center.y - PointR.y), 2)));;
public:
	Circ(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Circ();
	virtual void Draw(GUI* pUI) const;
};



