#include "Rect.h"

Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{


	ShpGfxInfo.ShapeType = "Rectangle";
	Corner1 = P1;
	Corner2 = P2;

}

void Rect::Load(ifstream &Infile){
	Infile>>ShpGfxInfo.ID;
	Point P1,P2;
	Infile>>P1.x;
	Infile>>P1.y;
	Infile>>P2.x;
	Infile>>P2.y;
	ShpGfxInfo.ShapeType="Rectangle";
	Corner1= P1;
	Corner2= P2;
	shape::Load(Infile);
}


Rect::~Rect(){}
Rect::Rect(){}
//
//Point Rect::getBorders() {
//	return Corner1;
//}


shape* Rect::clone() {
	shape* newShape = new Rect(*this);

	newShape->updateID(); return newShape;
}
void Rect::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}

void Rect::Save(ofstream& outfile) {

	outfile<<"Rect"<<" "<<ShpGfxInfo.ID<<" ";
	outfile<<Corner1.x<<" "<<Corner1.y<<" "<<Corner2.x<<" "<<Corner2.y<<" ";
	shape::Save(outfile);
}	//Save the shape parameters to the file

bool Rect::isInside(int x, int y) const {
	return((x <= max(Corner1.x, Corner2.x)) && (y <= max(Corner1.y, Corner2.y)) && (x >= min(Corner1.x, Corner2.x)) && (y >= min(Corner1.y, Corner2.y)));
}

void Rect::StickImageSh(GUI* pUI, string imagefile) {
	if (hasImage()) {
		double x = min(Corner1.x, Corner2.x); //the x coordinate of the image
		double y = min(Corner1.y, Corner2.y); //the y coordinate of the image 
		double wid = abs(Corner2.x - Corner1.x); //the width of the image
		double len = abs(Corner2.y - Corner1.y); //the length of the image
		pUI->StickImageGUI(imagefile, x, y, wid, len);
		setHasImage();
	}
}

ShapePoints Rect::getPoints() {
	ShapePoints RectP;
	RectP.P_num = 2;
	RectP.s_Points.resize(RectP.P_num);

	RectP.s_Points[0].x = this->Corner1.x;
	RectP.s_Points[0].y = this->Corner1.y;

	RectP.s_Points[1].x = this->Corner2.x;
	RectP.s_Points[1].y = this->Corner2.y;

	return RectP;
}

void Rect::MoveShape(Point MoveBy) {
	this->Corner1.x = this->Corner1.x + MoveBy.x;
	this->Corner1.y = this->Corner1.y + MoveBy.y;

	this->Corner2.x = this->Corner2.x + MoveBy.x;
	this->Corner2.y = this->Corner2.y + MoveBy.y;
}


void Rect::resizeSH(double num) {
	Point Center;
	Center.x = min(Corner1.x, Corner2.x) + abs(Corner1.x - Corner2.x) / 2;
	Center.y = min(Corner1.y, Corner2.y) + abs(Corner1.y - Corner2.y) / 2;
	double t1x = Corner1.x; double t1y = Corner1.y; double t2x = Corner2.x; double t2y = Corner2.y;
	Corner1.x = num * t1x - num * Center.x + Center.x; Corner1.y = num * t1y - num * Center.y + Center.y; Corner2.x = num * t2x - num * Center.x + Center.x; Corner2.y = num * t2y - num * Center.y + Center.y;
}
void Rect::rotateSH() {
	Point Center;
	double width = abs(Corner1.x - Corner2.x);
	double length = abs(Corner1.y - Corner2.y);
	Center.x = min(Corner1.x, Corner2.x) + width / 2;
	Center.y = min(Corner1.y, Corner2.y) + length / 2;
	double t1x = Corner1.x;
	double t1y = Corner1.y;
	double t2x = Corner2.x;
	double t2y = Corner2.y;


	Corner1.x = -(t1y)+(Center.x) + Center.y;
	Corner1.y = t1x - (Center.x) + Center.y;
	Corner2.x = -(t2y)+(Center.x) + Center.y;
	Corner2.y = t2x - (Center.x) + Center.y;
}

Point Rect::HideShape(Point DxDy) {
	if (!ShpGfxInfo.isHidden) {

		ShpGfxInfo.isHidden = true;
		Point Shp_dxdy;
		Point max_xy, min_xy, v_Center;
		double div_scale, ratX, ratY;

		max_xy = Corner1;
		min_xy = Corner2;
		v_Center = (max_xy + min_xy) / 2;

		Shp_dxdy = Shp_dxdy.abs(max_xy - min_xy);
		ratX = (double)DxDy.x / (double)Shp_dxdy.x;
		ratY = (double)DxDy.y / (double)Shp_dxdy.y;
		div_scale = min(ratX, ratY);
		(div_scale >= 1) ? div_scale = 1 : div_scale = div_scale;
		this->resizeSH(div_scale);
		this->ShpGfxInfo.HidId = this->ShpGfxInfo.GameID;
		return (v_Center - (DxDy / 2));
	}
}

void Rect::sethideID(int in_Hideid) {
	GfxInfo Tgfx = this->getGfxInfo();
	this->ShpGfxInfo.HidId = in_Hideid;
	this->isCard = true;
}
void Rect::Zoom(double Zf) {
	Point max_xy, min_xy, v_Center, CanvasCenter, Diff;
	CanvasCenter.x = 690; 	CanvasCenter.y = 475;
	max_xy = Corner1;
	min_xy = Corner2;
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