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
};



