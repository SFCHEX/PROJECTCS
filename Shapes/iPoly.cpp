#pragma once
#include "iPoly.h"

using namespace std;
iPoly::iPoly(vector<int> pVectiX, vector<int> pVectiY, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	ShpGfxInfo.ShapeType = "Irregular Polygon";
	pVectX = pVectiX;
	pVectY = pVectiY;
}


shape* iPoly::clone(){
	shape* newShape=new iPoly(*this);

	newShape->updateID(); return newShape;



}
iPoly::~iPoly() {}

void iPoly::Save(ofstream& outfile)
{
	for (int i=0; i<pVectX.size();i++)
	outfile<<pVectX[i]<<","<<pVectY[i]<<",";
}

void iPoly::Draw(GUI* pUI) const
{
	//Call Output::DrawiPoly to draw a iPoly on the screen	
	pUI->DrawiPoly(pVectX, pVectY , ShpGfxInfo);
}

bool iPoly::isInside(int x, int y) const
{
	//int max_X = *max_element(pVectX.begin(), pVectX.end());
	//int max_Y = *max_element(pVectY.begin(), pVectY.end());
	//int min_X = *min_element(pVectX.begin(), pVectX.end());
	//int min_Y = *min_element(pVectY.begin(), pVectY.end());
	//return (x >= min_X && x <= max_X && y >= min_Y && y <= max_Y);
	int num = pVectX.size();
	int i, j, c = 0;
	for (i = 0, j = num - 1; i < num; j = i++) {
		if (((pVectY[i] > y) != (pVectY[j] > y)) &&
			(x < (pVectX[j] - pVectX[i]) * (y - pVectY[i]) / (pVectY[j] - pVectY[i]) + pVectX[i]))
			c = !c;
	}
	return c;
}