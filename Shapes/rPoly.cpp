#pragma once
#include "rPoly.h"
#include <algorithm>
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

void rPoly::Load(ifstream &Infile){
	double px;
	double py;
	Infile>>ShpGfxInfo.ID;
	Infile>>num;
	Infile>>P1.x;
	Infile>>P1.y;
	Infile>>P2.x;
	Infile>>P2.y;
	ShpGfxInfo.ShapeType="rPoly";
	int rad = (sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2)));
	double ang = 360 / num;
	for (int i = 0; i < num; i++) {
		px = P1.x + (rad * cos(Convert(i * ang)));
		pVectX.push_back(px);
	}
	pVectX.push_back(pVectX.front());

	for (int i = 0; i < num; i++) {
		py = P1.y + (rad * sin(Convert(i * ang)));
		pVectY.push_back(py);
	}
	pVectY.push_back(pVectY.front());
	shape::Load(Infile);
}



rPoly::rPoly() {}
rPoly::~rPoly() {}


void rPoly::Save(ofstream& outfile)
{


	outfile<<"rPoly"<<" "<<ShpGfxInfo.ID<<" ";
	outfile << num<<" "<<P1.x << " " <<P1.y<< " "<< P2.x << " " << P2.y << " ";
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

void rPoly::MoveShape(Point MoveBy) {
	for (int i = 0; i < this->pVectX.size(); i++) {
		this->pVectX[i] = this->pVectX[i] + MoveBy.x;
		this->pVectY[i] = this->pVectY[i] + MoveBy.y;
	}
}

void rPoly::StickImageSh(GUI* pUI, string imagefile) {
	if (hasImage()) {
		double x = min(P2.x, P1.x)- (abs(P2.x - P1.x)/2); //the x coordinate of the image
		double y = min(P1.y, P2.y)-(abs(P2.x - P1.x)/2); //the y coordinate of the image 
		double wid = abs(P2.x - P1.x); //the width of the image
		double len = abs(P2.x - P1.x); //the length of the image //same as width because it is a square image
		pUI->StickImageGUI(imagefile, x, y, wid, len);
		setHasImage();
	}
}

void rPoly::resizeSH(double numb) {
	for (int i = 0; i < num+1; i++) {
		pVectX[i] = (numb * pVectX[i]) - (numb * P1.x) + P1.x;
		pVectY[i] = (numb * pVectY[i]) - (numb * P1.y) + P1.y;
	}
}
	
void rPoly::rotateSH() {
	for (int i = 0; i < num + 1; i++) {
		double tx = pVectX[i]; double ty = pVectY[i];
		pVectX[i] = -ty + (P1.x) + P1.y;
		pVectY[i] = tx - (P1.x) + P1.y;
	}
}

Point rPoly::HideShape(Point DxDy) {
	if (!ShpGfxInfo.isHidden) {

		ShpGfxInfo.isHidden = true;
		Point Shp_dxdy;
		Point max_xy, min_xy, v_Center;
		double div_scale, ratX, ratY;

		max_xy.x = *max_element(pVectX.begin(), pVectX.end());
		max_xy.y = *max_element(pVectY.begin(), pVectY.end());

		min_xy.x = *min_element(pVectX.begin(), pVectX.end());
		min_xy.y = *min_element(pVectY.begin(), pVectY.end());
		v_Center = (max_xy + min_xy) / 2;


		Shp_dxdy = Shp_dxdy.abs(max_xy - min_xy);
		ratX = (double)DxDy.x / (double)Shp_dxdy.x;
		ratY = (double)DxDy.y / (double)Shp_dxdy.y;
		div_scale = min(ratX, ratY);
		(div_scale >= 1) ? div_scale = 1 : div_scale = div_scale;
		this->resizeSH(div_scale - 0.05);
		return (v_Center - (DxDy / 2));
	}
}
void rPoly::Zoom(double Zf) {
	Point max_xy, min_xy, v_Center, CanvasCenter, Diff;
	CanvasCenter.x = 690; 	CanvasCenter.y = 375;
	max_xy.x = *max_element(pVectX.begin(), pVectX.end());
	max_xy.y = *max_element(pVectY.begin(), pVectY.end());

	min_xy.x = *min_element(pVectX.begin(), pVectX.end());
	min_xy.y = *min_element(pVectY.begin(), pVectY.end());
	v_Center = (max_xy + min_xy) / 2;

	if (Zf > 1) {
		Diff = (v_Center - CanvasCenter) * (Zf - 1);
		Diff = Diff / 1;
	}
	else {
		Diff = (v_Center - CanvasCenter);
		Diff = Diff * (-Zf / 1.0);

	}
	this->MoveShape(Diff);
	this->resizeSH(Zf);
}