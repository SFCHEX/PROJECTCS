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

void iPoly::MoveShape(Point MoveBy) {
	for (int i = 0; i < this->pVectX.size(); i++) {
		this->pVectX[i] = this->pVectX[i] + MoveBy.x;
		this->pVectY[i] = this->pVectY[i] + MoveBy.y;
	}
}

void iPoly::StickImageSh(GUI* pUI, string imagefile) {
	if (hasImage()) {
		Point Center;
		double sumx = 0; double sumy = 0;
		
		for (int i = 0; i < pVectX.size(); i++) {
			sumx += pVectX[i]; sumy += pVectY[i];
		}
		Center.x = sumx / pVectX.size(); Center.y = sumy / pVectY.size();
		double minx =Center.x ,miny=Center.y ,maxx=Center.x ,maxy=Center.y ;
		for (int i = 0; i < pVectX.size(); i++) {
			if(pVectX[i]<minx) minx=pVectX[i];
			if(pVectX[i]>maxx) maxx=pVectX[i];
			if(pVectY[i]<miny) miny=pVectY[i];
			if(pVectY[i]>maxy) maxy=pVectY[i];
		}
		
		double wid = maxx - minx; //the width of the image
		double len = maxy - miny; //the length of the image //same as width because it is a square image
		pUI->StickImageGUI(imagefile, minx, miny, wid, len);
		setHasImage();
	}
}
void iPoly::rotateSH() {
	Point Center;
	double sumx = 0; double sumy = 0;
	for (int i = 0; i < pVectX.size(); i++) {
		sumx += pVectX[i]; sumy += pVectY[i];
	}
	Center.x = sumx / pVectX.size(); Center.y = sumy / pVectY.size();
	for (int i = 0; i < pVectX.size(); i++) {
		double tx = pVectX[i]; double ty = pVectY[i];
		pVectX[i] = -ty  + (Center.x) + Center.y;
		pVectY[i] = tx - (Center.x) + Center.y;
	}
}


void iPoly::resizeSH(double n) {
	Point Center;
	double sumx = 0; double sumy = 0;
	for (int i = 0; i < pVectX.size(); i++) {
		sumx += pVectX[i]; sumy += pVectY[i];
	}
	Center.x = sumx / pVectX.size(); Center.y = sumy / pVectY .size();
	for (int i = 0; i < pVectX.size(); i++) {
		pVectX[i] = (n * pVectX[i]) - (n * Center.x) + Center.x;
		pVectY[i] = (n * pVectY[i]) - (n * Center.y) + Center.y;
	}
}