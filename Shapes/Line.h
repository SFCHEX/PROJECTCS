#pragma once
#include "Shape.h"
class Lines : public shape
{
private:
	Point End1;
	Point End2;
public:
	Lines(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Lines();
	virtual void Draw(GUI* pUI) const;
};

