#include "Square.h"
#include <math.h>

//#include <cstdlib>
//#include <ctime>
Square::Square(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo){

	ShpGfxInfo.ShapeType="Square";
	//the if statements determine which corner we started at however shape is always
	//drawn bottom to top and left to right
	if ((abs(P2.x - P1.x) > abs(P2.y - P1.y)) && ((P2.x - P1.x)) > 0) {
		Corner1 = P1;
		Corner2.x = P2.x;
		Corner2.y = (P1.y - (P2.x - P1.x));
	}
	else if ((abs(P2.x - P1.x) > abs(P2.y - P1.y)) && ((P2.x - P1.x)) < 0) {
		Corner1 = P1;
		Corner2.x = P2.x;
		Corner2.y = (P1.y + (P2.x - P1.x));
	}
	else if ((abs(P2.x - P1.x) < abs(P2.y - P1.y)) && ((P2.y - P1.y) < 0)) {
		Corner1 = P1;
		Corner2.y = P2.y;
		Corner2.x = (P1.x + (P1.y - P2.y));
	}
	else if ((abs(P2.x - P1.x) < abs(P2.y - P1.y)) && ((P2.y - P1.y) > 0)) {
		Corner1 = P1;
		Corner2.y = P2.y;
		Corner2.x = (P1.x + (P2.y - P1.y));
	}
	else if (abs(P2.x - P1.x) == (abs(P2.y - P1.y))) {
		Corner1 = P1;
		Corner2 = P2;
	}


}

shape* Square::clone(){
	shape* newShape=new Square(*this);

	newShape->updateID(); return newShape;
}	

Square::~Square(){}

void Square::Draw(GUI* pUI) const {
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}

void Square::Save(ofstream &outfile){

	outfile<<"Square"<<","<<ShpGfxInfo.ID<<",";
	outfile << Corner1.x << "," << Corner1.y << "," << Corner2.x << "," << Corner2.y << ",";
	shape::Save(outfile);
}	//Save the shape parameters to the file

bool Square::isInside(int x, int y) const { 
	return((x <= max(Corner1.x, Corner2.x)) && (y <= max(Corner1.y, Corner2.y)) && (x >= min(Corner1.x, Corner2.x)) && (y >= min(Corner1.y, Corner2.y)));
}

void Square::StickImageSh(GUI* pUI, string imagefile) {
	if (hasImage()) {
		double x = min(Corner1.x, Corner2.x); //the x coordinate of the image
		double y = min(Corner1.y, Corner2.y); //the y coordinate of the image 
		double wid = abs(Corner2.x - Corner1.x); //the width of the image
		double len = abs(Corner2.y - Corner1.y); //the length of the image
		pUI->StickImageGUI(imagefile, x, y, wid, len);
		setHasImage();
	}
}

void Square::scramble(Point p)
{
	Point max_xy, min_xy, v_Center, diff;
	max_xy = Corner1;
	min_xy = Corner2;
	v_Center = (max_xy + min_xy) / 2;
	diff.x = abs(p.x - v_Center.x);
	diff.y = abs(p.y - v_Center.y);
	if (p.x > v_Center.x && p.y > v_Center.y)
	{
		this->MoveShape(diff);
	}
	else if (p.x < v_Center.x && p.y < v_Center.y)
	{
		diff.x = -diff.x;
		diff.y = -diff.y;
		this->MoveShape(diff);

	}
	else if (p.x < v_Center.x && p.y > v_Center.y)
	{
		diff.x = -diff.x;
		this->MoveShape(diff);

	}
	else if (p.x > v_Center.x && p.y < v_Center.y)
	{
		diff.y = -diff.y;
		this->MoveShape(diff);

	}

}
ShapePoints Square::getPoints() {
	ShapePoints SquareP;
	SquareP.P_num = 2;
	SquareP.s_Points.resize(SquareP.P_num);

	SquareP.s_Points[0].x = this->Corner1.x;
	SquareP.s_Points[0].y = this->Corner1.y;

	SquareP.s_Points[1].x = this->Corner2.x;
	SquareP.s_Points[1].y = this->Corner2.y;

	return SquareP;
}

void Square::MoveShape(Point MoveBy) {
	this->Corner1.x = this->Corner1.x + MoveBy.x;
	this->Corner1.y = this->Corner1.y + MoveBy.y;

	this->Corner2.x = this->Corner2.x + MoveBy.x;
	this->Corner2.y = this->Corner2.y + MoveBy.y;
}

void Square::resizeSH(double n){
	Point Center;
	double width = abs(Corner1.x - Corner2.x);
	double length = abs(Corner1.y - Corner2.y);
	Center.x = min(Corner1.x,Corner2.x)+ width/2;
	Center.y = min(Corner1.y,Corner2.y)+ length/2;
	
	
	Corner1.x = (n * Corner1.x) - (n * Center.x) + Center.x;
	Corner1.y = (n * Corner1.y) - (n * Center.y) + Center.y;
	Corner2.x = (n * Corner2.x) - (n * Center.x) + Center.x;;
	Corner2.y = (n * Corner2.y) - (n * Center.y) + Center.y;;
	
}
void Square::rotateSH(){
	
}

string Square::match()
{
	return this->ShpGfxInfo.ShapeType;
}