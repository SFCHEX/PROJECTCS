#include "Square.h"
#include <math.h>
#include <iostream>
using namespace std;
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

void Square::Load(ifstream &Infile){
	cout<<"Im in the virtual load for square";
	Infile>>ShpGfxInfo.ID;
	cout<<"id";
	Point P1,P2;
	cout<<"point";
	Infile>>P1.x;
	Infile>>P1.y;
	Infile>>P2.x;
	Infile>>P2.y;
	cout<<"shapetype";
	ShpGfxInfo.ShapeType="Square";
	Corner1= P1;
	Corner2= P2;
	shape::Load(Infile);
}


shape* Square::clone(){
	shape* newShape=new Square(*this);

	newShape->updateID(); return newShape;
}	

Square::~Square(){}
Square::Square(){}

void Square::Draw(GUI* pUI) const {
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}

void Square::Save(ofstream &outfile){

	outfile<<"Square"<<" "<<ShpGfxInfo.ID<<" ";
	outfile << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << " ";
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

//void Square::scramble()
//{
//
//		srand(time(0));
//
//		int x = rand() % 1301;
//		int y = rand() % 500;
//
//		if (Corner1.x + x < 1300 && Corner2.x + x < 1300 && Corner1.y + y > 100 && Corner2.y + y > 100)
//		{
//			if (Corner1.y + y < 650 && Corner2.y + y < 650)
//			{
//				Corner1.x += x;
//				Corner1.y += y;
//				Corner2.x += x;
//				Corner2.y += y;
//			}
//	
//		}
//		else
//		{
//			Corner1.x -= x;
//			Corner1.y -= y;
//			Corner2.x -= x;
//			Corner2.y -= y;
//		}
//		x = 0;
//		y = 0;
//
//}
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