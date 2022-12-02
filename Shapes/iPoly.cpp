#pragma once
#include "iPoly.h"

iPoly::iPoly(vector<int> pVectiX, vector<int> pVectiY, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	ShpGfxInfo.ShapeType = "Irregular Polygon";
	pVectX = pVectiX;
	pVectY = pVectiY;
}

iPoly::~iPoly() {}


string iPoly::GetShapeType() const {
	return "iPoly";
}
void iPoly::Save(ofstream& outfile)
{
	for (int i=0; i<pVectX.size();i++)
	outfile<<pVectX[i]<<","<<pVectY[i]<<",";
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
