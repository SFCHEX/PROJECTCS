#include "Circ.h"
#include <iostream>
using namespace std;
Circ::Circ(Point P1, Point P2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{

	ShpGfxInfo.ShapeType="Circle";
	Center = P1;
	PointR = P2;
	ShpGfxInfo.isHidden = false;

}
Circ::Circ(){

}

void Circ::Load(ifstream &Infile){
	Infile>>ShpGfxInfo.ID;
	Point P1,P2;
	Infile>>P1.x;
	Infile>>P1.y;
	Infile>>P2.x;
	Infile>>P2.y;
	ShpGfxInfo.ShapeType="Circle";
	Center = P1;
	PointR = P2;
	shape::Load(Infile);
}




shape* Circ::clone(){
	shape* newShape=new Circ(*this);

	newShape->updateID(); return newShape;
}
Circ::~Circ()
{}
void Circ::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawCirc(Center, PointR, ShpGfxInfo);
}

void Circ::Save(ofstream &outfile){

	outfile<<"Circle"<<" "<<ShpGfxInfo.ID<<" ";
	outfile<<Center.x<<" "<<Center.y<<" "<<PointR.x<<" "<<PointR.y<<" ";
	shape::Save(outfile);
}	//Save the shape parameters to the file

bool Circ::isInside(int x, int y) const{
	double RealRadius = (sqrt(pow((Center.x - PointR.x), 2) + pow((Center.y - PointR.y), 2)));
	double TestRadius = (sqrt(pow((Center.x - x), 2) + pow((Center.y - y), 2)));
	if (RealRadius >= TestRadius) {
		return true;
	}
	else {
		return false;
	}
}

ShapePoints Circ::getPoints() {
	ShapePoints CircP;
	CircP.P_num = 2;
	CircP.s_Points.resize(CircP.P_num);
	
	CircP.s_Points[0].x = this->Center.x;
	CircP.s_Points[0].y = this->Center.y;

	CircP.s_Points[1].x = this->PointR.x;
	CircP.s_Points[1].y = this->PointR.y;

	return CircP;
}

void Circ::MoveShape(Point MoveBy) {
	this->Center.x = this->Center.x + MoveBy.x;
	this->Center.y = this->Center.y + MoveBy.y;

	this->PointR.x = this->PointR.x + MoveBy.x;
	this->PointR.y = this->PointR.y + MoveBy.y;
}

void Circ::StickImageSh(GUI* pUI, string imagefile) {
	if (hasImage()) {
		double r = sqrt((Center.x - PointR.x) * (Center.x - PointR.x) + (Center.y - PointR.y) * (Center.y - PointR.y));
		double x = Center.x - (sqrt(2) / 2) * r; //the x coordinate of the image
		double y = Center.y - (sqrt(2) / 2) * r; //the y coordinate of the image 
		double wid = sqrt(2) *r; //the width of the image
		double len = sqrt(2) *r; //the length of the image
		pUI->StickImageGUI(imagefile, x, y, wid, len);
	}
}
 
//void Circ::scramble()
//{
//	srand(time(0));
//	int x = rand() % 1301;
//	int y = rand() % 500;
//
//	if (Center.x + x < 1300 && Center.y + y > 100 && Center.y + y < 650)
//	{
//
//			Center.x += x;
//			Center.y += y;
//			PointR.x += x;
//			PointR.y += y;
//		
//	}
//	else
//	{
//		Center.x -= x;
//		Center.y -= y;
//	}
//
//}

void Circ::resizeSH(double num) {
	if (num >= 1) {
		PointR.x = Center.x + num * abs(PointR.x - Center.x);
		PointR.y = Center.y + num * abs(PointR.y - Center.y);
	}
	else {
		PointR.x = abs(PointR.x - Center.x) * (num)+Center.x;
		PointR.y = abs(PointR.y - Center.y) * (num)+Center.y;
	}

}

Point Circ::HideShape(Point DxDy) {
	if (!ShpGfxInfo.isHidden) {
		ShpGfxInfo.isHidden = true;
		Point Shp_dxdy;
		Point max_xy, min_xy, v_Center;
		double div_scale, ratX, ratY;
		int rad = (sqrt(pow((Center.x - PointR.x), 2) + pow((Center.y - PointR.y), 2)));
		max_xy.x = Center.x + rad;
		max_xy.y = Center.y + rad;
		min_xy.x = Center.x - rad;
		min_xy.y = Center.y - rad;
		v_Center = Center;

		Shp_dxdy = Shp_dxdy.abs(max_xy - min_xy);
		ratX = (double)DxDy.x / (double)Shp_dxdy.x;
		ratY = (double)DxDy.y / (double)Shp_dxdy.y;
		div_scale = min(ratX, ratY);
		(div_scale >= 1) ? div_scale = 1 : div_scale = div_scale;
		this->resizeSH(div_scale);
		return (v_Center - (DxDy / 2));
	}
}
void Circ::Zoom(double Zf) {
	Point max_xy, min_xy, v_Center, CanvasCenter, Diff;
	CanvasCenter.x = 690; 	CanvasCenter.y = 375;
	v_Center = Center;
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