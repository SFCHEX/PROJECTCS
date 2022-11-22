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
};

