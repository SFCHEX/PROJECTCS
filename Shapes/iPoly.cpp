#pragma once
#include "iPoly.h"

using namespace std;
iPoly::iPoly(vector<int> pVectiX, vector<int> pVectiY, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
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


	outfile<<"iPoly"<<","<<ShpGfxInfo.ID<<",";
	for (int i=0; i<pVectX.size();i++)
	outfile<<pVectX[i]<<","<<pVectY[i]<<",";
	shape::Save(outfile);
}

void iPoly::Draw(GUI* pUI) const
{
	//Call Output::DrawiPoly to draw a iPoly on the screen	
	pUI->DrawiPoly(pVectX, pVectY , ShpGfxInfo);
}

bool iPoly::isInside(int x, int y) const
{
	int num = pVectX.size();
	int i, j, c = 0;
	for (i = 0, j = num - 1; i < num; j = i++) {
		if (((pVectY[i] > y) != (pVectY[j] > y)) &&
			(x < (pVectX[j] - pVectX[i]) * (y - pVectY[i]) / (pVectY[j] - pVectY[i]) + pVectX[i]))
			c = !c;
	}
	return c;
}

ShapePoints iPoly::getPoints() {
	ShapePoints iPolyP;
	iPolyP.P_num = this->pVectX.size();
	iPolyP.s_Points.resize(iPolyP.P_num);

	for (int i = 0; i < iPolyP.P_num; i++) {
		iPolyP.s_Points[i].x = this->pVectX[i];
		iPolyP.s_Points[i].y = this->pVectY[i];
	}

	return iPolyP;
}