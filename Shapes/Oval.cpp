#include "Oval.h"

Oval::Oval(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ShpGfxInfo.ShapeType="Oval";
	Corner1 = P1;
	Corner2 = P2;
}

Oval::~Oval()
{}

void Oval::Draw(GUI* pUI) const
{
	//Call Output::DrawOval to draw a Ovalangle on the screen	
	pUI->DrawOval(Corner1, Corner2, ShpGfxInfo);
}