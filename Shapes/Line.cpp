#include "Line.h"

Lines::Lines(Point p1, Point p2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	End1 = p1;
	End2 = p2;
}

Lines::~Lines() {}

void Lines::Draw(GUI* pUI) const
{
	pUI->DrawLines(End1, End2, ShpGfxInfo);
}