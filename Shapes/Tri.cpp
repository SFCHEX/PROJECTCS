#include "Tri.h"
#include <algorithm>
Tri::Tri(Point P1, Point P2, Point P3, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{

	ShpGfxInfo.ShapeType="Triangle";
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;

}

Tri::~Tri()
{}

void Tri::Draw(GUI* pUI) const
{
	//Call Output::DrawTri to draw a Triangle on the screen	
	pUI->DrawTri(Corner1, Corner2, Corner3, ShpGfxInfo);
}

double Tri::Area(int x1, int y1, int x2, int y2, int x3, int y3) const {
	double triarea;
	triarea = abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2);
	return triarea;
}

void Tri::Save(ofstream &outfile){

	outfile<<"Triangle"<<","<<ShpGfxInfo.ID<<",";
	outfile<<Corner1.x<<","<<Corner1.y<<","<<Corner2.x<<","<<Corner2.y<<","<<Corner3.x<<","<<Corner3.y<<",";
	shape::Save(outfile);

}	//Save the shape parameters to the file

shape* Tri::clone(){
	shape* newShape= new Tri(*this);
	newShape->updateID(); return newShape;
}



bool Tri::isInside(int x, int y) const
{
	int num = 3;
	int i, j, c = 0;
	int pVectX[3] = { Corner1.x, Corner2.x, Corner3.x };
	int pVectY[3] = { Corner1.y, Corner2.y, Corner3.y };
	for (i = 0, j = num - 1; i < num; j = i++) {
		if (((pVectY[i] > y) != (pVectY[j] > y)) &&
			(x < (pVectX[j] - pVectX[i]) * (y - pVectY[i]) / (pVectY[j] - pVectY[i]) + pVectX[i]))
			c = !c;
	}
	return c;
}
void Tri::StickImageSh(GUI* pUI, string imagefile) {
	double centroidx = (Corner1.x + Corner2.x + Corner3.x) / 3;
	double centroidy = (Corner1.y + Corner2.y + Corner3.y) / 3;
	double x = centroidx - 40;
	double y = centroidy - 40;
	double len = 100;
	double wid = 100;
	pUI->StickImageGUI(imagefile, x, y, wid, len);
	setHasImage();
}
ShapePoints Tri::getPoints() {
	ShapePoints TriP;
	TriP.P_num = 3;
	TriP.s_Points.resize(TriP.P_num);

	TriP.s_Points[0].x = this->Corner1.x;
	TriP.s_Points[0].y = this->Corner1.y;

	TriP.s_Points[1].x = this->Corner2.x;
	TriP.s_Points[1].y = this->Corner2.y;

	TriP.s_Points[2].x = this->Corner3.x;
	TriP.s_Points[2].y = this->Corner3.y;

	return TriP;
}

void Tri::MoveShape(Point MoveBy) {
	this->Corner1.x = this->Corner1.x + MoveBy.x;
	this->Corner1.y = this->Corner1.y + MoveBy.y;

	this->Corner2.x = this->Corner2.x + MoveBy.x;
	this->Corner2.y = this->Corner2.y + MoveBy.y;

	this->Corner3.x = this->Corner3.x + MoveBy.x;
	this->Corner3.y = this->Corner3.y + MoveBy.y;
}
void Tri::resizeSH(double n) {
	Point Centeriod;
	Centeriod.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	Centeriod.y = (Corner1.y + Corner2.y + Corner3.y) / 3; double t1x = Corner1.x;
	double t1y = Corner1.y;
	double t2x = Corner2.x;
	double t2y = Corner2.y;
	double t3x = Corner3.x;
	double t3y = Corner3.y;

	Corner1.x = (n * t1x) - (n *Centeriod.x) + Centeriod.x;
	Corner1.y = (n * t1y) - (n *Centeriod.y) + Centeriod.y;
	Corner2.x = (n * t2x) - (n *Centeriod.x) + Centeriod.x;
	Corner2.y = (n * t2y) - (n *Centeriod.y) + Centeriod.y;
	Corner3.x = (n * t3x) - (n *Centeriod.x) + Centeriod.x;
	Corner3.y = (n * t3y) - (n *Centeriod.y) + Centeriod.y;
}
void Tri::rotateSH(){
	Point Centeriod;
	Centeriod.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	Centeriod.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
	double t1x = Corner1.x;
	double t1y = Corner1.y;
	double t2x = Corner2.x;
	double t2y = Corner2.y;
	double t3x = Corner3.x;
	double t3y = Corner3.y;


	Corner1.x = -t1y +Centeriod.x + Centeriod.y;
	Corner1.y = t1x - Centeriod.x + Centeriod.y;
	Corner2.x = -t2y + Centeriod.x + Centeriod.y;
	Corner2.y = t2x - Centeriod.x + Centeriod.y;
	Corner3.x = -t3y + Centeriod.x + Centeriod.y;
	Corner3.y = t3x - Centeriod.x + Centeriod.y;
}

void Tri::HideShape(Point DxDy) {
	ShpGfxInfo.isHidden = true;
	Point Shp_dxdy;
	Point max_xy, min_xy, V_Center;
	double div_scale;

	max_xy.x = max(Corner1.x, max(Corner2.x, Corner3.x));
	max_xy.y = max(Corner1.y, max(Corner2.y, Corner3.y));

	min_xy.x = min(Corner1.x, min(Corner2.x, Corner3.x));
	min_xy.y = min(Corner1.y, min(Corner2.y, Corner3.y));
	v_Center = (max_xy + min_xy) / 2;


	Shp_dxdy = max_xy - min_xy;
	div_scale = max((abs((Shp_dxdy.y) / (DxDy.y))), abs(((Shp_dxdy.x) / (DxDy.x))));
	(div_scale >= 1) ? div_scale = 1 : div_scale = div_scale;
	this->resizeSH(1/div_scale);
}