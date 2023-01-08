#include "Tri.h"
#include <algorithm>
Tri::Tri(Point P1, Point P2, Point P3, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{

	ShpGfxInfo.ShapeType="Triangle";
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;

}

void Tri::Load(ifstream &Infile){
	Infile>>ShpGfxInfo.ID;
	Point P1,P2,P3;
	Infile>>P1.x;Infile>>P1.y;
	Infile>>P2.x;Infile>>P2.y;
	Infile>>P3.x;Infile>>P3.y;
	ShpGfxInfo.ShapeType="Triangle";
	Corner1= P1;
	Corner2= P2;
	Corner3= P3;
	shape::Load(Infile);
}


Tri::~Tri()
{}
Tri::Tri()
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

	outfile<<"Triangle"<<" "<<ShpGfxInfo.ID<<" ";
	outfile<<Corner1.x<<" "<<Corner1.y<<" "<<Corner2.x<<" "<<Corner2.y<<" "<<Corner3.x<<" "<<Corner3.y<<" ";
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
	
	double minx = min(min(Corner1.x, Corner2.x), Corner3.x);
	double miny = min(min(Corner1.y, Corner2.y), Corner3.y);
	double maxx = max(max(Corner1.x, Corner2.x), Corner3.x);
	double maxy = max(max(Corner1.y, Corner2.y), Corner3.y);
	double len = maxy - miny;
	double wid = maxx - minx;
	pUI->StickImageGUI(imagefile, minx, miny, wid, len);
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
	////
	Point max_xy, min_xy, Centeriod;

	max_xy.x = max(Corner1.x, max(Corner2.x, Corner3.x));
	max_xy.y = max(Corner1.y, max(Corner2.y, Corner3.y));

	min_xy.x = min(Corner1.x, min(Corner2.x, Corner3.x));
	min_xy.y = min(Corner1.y, min(Corner2.y, Corner3.y));
	Centeriod = (max_xy + min_xy) / 2;
	
	double t1x = Corner1.x;
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

Point Tri::HideShape(Point DxDy) {
	if (!ShpGfxInfo.isHidden) {

		ShpGfxInfo.isHidden = true;
		Point Shp_dxdy;
		Point max_xy, min_xy, v_Center;
		double div_scale,ratX, ratY;

		max_xy.x = max(Corner1.x, max(Corner2.x, Corner3.x));
		max_xy.y = max(Corner1.y, max(Corner2.y, Corner3.y));

		min_xy.x = min(Corner1.x, min(Corner2.x, Corner3.x));
		min_xy.y = min(Corner1.y, min(Corner2.y, Corner3.y));
		v_Center = (max_xy + min_xy) / 2;

		Shp_dxdy = Shp_dxdy.abs(max_xy - min_xy);
		ratX = (double)DxDy.x / (double)Shp_dxdy.x;
		ratY = (double)DxDy.y / (double)Shp_dxdy.y;
		div_scale = min(ratX, ratY);
		(div_scale >= 1) ? div_scale = 1 : div_scale = div_scale - 0.1;
		this->resizeSH(div_scale);
		this->ShpGfxInfo.HidId = this->ShpGfxInfo.GameID;
		return (v_Center - (DxDy / 2));

	}
}
void Tri::Zoom(double Zf) {
	Point max_xy, min_xy, v_Center, CanvasCenter, Diff;
	CanvasCenter.x = 690; 	CanvasCenter.y = 375;
	max_xy.x = max(Corner1.x, max(Corner2.x, Corner3.x));
	max_xy.y = max(Corner1.y, max(Corner2.y, Corner3.y));

	min_xy.x = min(Corner1.x, min(Corner2.x, Corner3.x));
	min_xy.y = min(Corner1.y, min(Corner2.y, Corner3.y));
	v_Center = (max_xy + min_xy) / 2;
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