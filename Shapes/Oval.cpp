#include "Oval.h"

Oval::Oval(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ShpGfxInfo.ShapeType="Oval";
	Corner1 = P1;
	Corner2 = P2;



}

void Oval::StickImageSh(GUI* pUI, string imagefile) {
	if (hasImage()){
		double x = min(Corner1.x, Corner2.x); //the x coordinate of the image
		double y = abs((Corner1.y + Corner2.y) / 2) - abs((Corner1.y - Corner2.y) / 4); //the y coordinate of the image //NEEDS UPDATE
		double wid = abs(Corner2.x - Corner1.x); //the width of the image
		double len = abs(Corner2.y - Corner1.y)/2; //the length of the image
		pUI->StickImageGUI(imagefile, x, y, wid, len);
		setHasImage();
	}
}

shape* Oval::clone(){
	shape* newShape=new Oval(*this);

	newShape->updateID(); return newShape;

}	
Oval::~Oval()
{}

void Oval::Draw(GUI* pUI) const
{

	//Call Output::DrawOval to draw a Ovalangle on the screen	
	pUI->DrawOval(Corner1, Corner2, ShpGfxInfo);
}
void Oval::Save(ofstream &outfile){

	outfile<<"Oval"<<","<<ShpGfxInfo.ID<<",";
	outfile<<Corner1.x<<","<<Corner1.y<<","<<Corner2.x<<","<<Corner2.y<<",";
	shape::Save(outfile);
}	//Save the shape parameters to the file

bool Oval::isInside(int x, int y) const {
	double radX = abs((Corner1.x - Corner2.x)/2);
	double radY = abs((Corner1.y - Corner2.y)/2);
	double centX = abs((Corner1.x + Corner2.x)/2);
	double centY = abs((Corner1.y + Corner2.y)/2);

	return (((pow((x - centX), 2)) / (pow(radX, 2))) + ((pow((y - centY), 2)) / (pow(radY, 2)))) <= 1;
}

ShapePoints Oval::getPoints() {
	ShapePoints OvalP;
	OvalP.P_num = 2;
	OvalP.s_Points.resize(OvalP.P_num);

	OvalP.s_Points[0].x = this->Corner1.x;
	OvalP.s_Points[0].y = this->Corner1.y;

	OvalP.s_Points[1].x = this->Corner2.x;
	OvalP.s_Points[1].y = this->Corner2.y;

	return OvalP;
}

void Oval::MoveShape(Point MoveBy) {
	this->Corner1.x = this->Corner1.x + MoveBy.x;
	this->Corner1.y = this->Corner1.y + MoveBy.y;

	this->Corner2.x = this->Corner2.x + MoveBy.x;
	this->Corner2.y = this->Corner2.y + MoveBy.y;
}
void Oval::resizeSH(double num) {
	Point Center;
	Center.x = min(Corner1.x, Corner2.x) + abs(Corner1.x - Corner2.x)/2;
	Center.y = min(Corner1.y, Corner2.y) + abs(Corner1.y - Corner2.y) / 2;
    double t1x = Corner1.x; double t1y = Corner1.y; double t2x = Corner2.x; double t2y = Corner2.y;
    Corner1.x = num*t1x - num*Center.x +Center.x; Corner1.y = num*t1y -num*Center.y + Center.y; Corner2.x = num*t2x - num*Center.x +Center.x; Corner2.y = num*t2y -num*Center.y + Center.y; 
}


void Oval::rotateSH() {
	Point Center;
	Center.x = min(Corner1.x, Corner2.x) + abs(Corner1.x - Corner2.x)/2;
	Center.y = min(Corner1.y, Corner2.y) + abs(Corner1.y - Corner2.y) / 2;
	double t1x = Corner1.x; double t1y = Corner1.y;
	double t2x = Corner2.x; double t2y = Corner2.y;
	
	Corner1.x = -t1y + Center.x + Center.y;
	Corner1.y = t1x - Center.x + Center.y;
	Corner2.x = -t2y + Center.x + Center.y;
	Corner2.y = t2x - Center.x + Center.y;
	
}