#include "Circ.h"

Circ::Circ(Point P1, Point P2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	Center = P1;
	PointR = P2;
}

Circ::~Circ()
{}


void Circ::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawCirc(Center, PointR, ShpGfxInfo);
}