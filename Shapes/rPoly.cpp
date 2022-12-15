#pragma once
#include "rPoly.h"

using namespace std;


double rPoly::Convert(double degree)
{
	double pi = 3.14159265359;
	return (degree * (2*pi / 360));
}

shape* rPoly::clone(){
	shape* newShape=new rPoly(*this);

	newShape->updateID(); return newShape;
}	
rPoly::rPoly(int nSides, Point pCenter, Point pRadius, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	P1=pCenter;
	P2=pRadius;
	ShpGfxInfo.ShapeType = "Regular Polygon";
	double ang = 360 / nSides;
	double px;
	double py;
	int rad = (sqrt(pow((pCenter.x - pRadius.x), 2) + pow((pCenter.y - pRadius.y), 2)));
	num = nSides;
	


	for (int i = 0; i < nSides; i++) {
		px = pCenter.x + (rad * cos(Convert(i * ang)));
		pVectX.push_back(px);
	}
	pVectX.push_back(pVectX.front());

	for (int i = 0; i < nSides; i++) {
		py = pCenter.y + (rad * sin(Convert(i * ang)));
		pVectY.push_back(py);
	}
	pVectY.push_back(pVectY.front());
}

rPoly::~rPoly() {}


void rPoly::Save(ofstream& outfile)
{


	outfile<<"rPoly"<<","<<ShpGfxInfo.ID<<",";
	outfile << num<<","<<P1.x << "," <<P1.y<< ","<< P2.x << "," << P2.y << ",";
	shape::Save(outfile);
}

void rPoly::Draw(GUI* pUI) const
{
	//Call Output::DrawrPoly to draw a rPoly on the screen	
	pUI->DrawrPoly(pVectX, pVectY, ShpGfxInfo);
}

bool rPoly::isInside(int x, int y) const
{

	int i, j, c = 0;
	for (i = 0, j = num - 1; i < num; j = i++) {
		if (((pVectY[i] > y) != (pVectY[j] > y)) &&
			(x < (pVectX[j] - pVectX[i]) * (y - pVectY[i]) / (pVectY[j] - pVectY[i]) + pVectX[i]))
			c = !c;
	}
	return c;
}

ShapePoints rPoly::getPoints() {
	ShapePoints rPolyP;
	rPolyP.P_num = this->pVectX.size();
	rPolyP.s_Points.resize(rPolyP.P_num);

	for (int i = 0; i < rPolyP.P_num; i++) {
		rPolyP.s_Points[i].x = this->pVectX[i];
		rPolyP.s_Points[i].y = this->pVectY[i];
	}

	return rPolyP;
}