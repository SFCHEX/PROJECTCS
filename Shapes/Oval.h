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
	virtual ~Oval();
	virtual void Draw(GUI* pUI) const;
};

