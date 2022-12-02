#pragma once
#include "iPoly.h"

iPoly::iPoly(vector<int> pVectiX, vector<int> pVectiY, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	ShpGfxInfo.ShapeType = "iPolyangle";
	pVectX = pVectiX;
	pVectY = pVectiY;
}

iPoly::~iPoly() {}


string iPoly::GetShapeType() const {
	return "iPoly";
}
void iPoly::Save(ofstream& outfile)
{
}
bool iPoly::isInside(int x, int y) const
{
	return false;
}
void iPoly::Draw(GUI* pUI) const
{
	//Call Output::DrawiPoly to draw a iPoly on the screen	
	pUI->DrawiPoly(pVectX, pVectY , ShpGfxInfo);
}
