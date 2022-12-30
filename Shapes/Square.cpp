#include "Square.h"
#include <math.h>

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

void Square::resizeSH(double num){
	Point Center;
	double width = abs(Corner1.x - Corner2.x);
	double length = abs(Corner1.y - Corner2.y);
	Center.x = min(Corner1.x,Corner2.x)+ width/2;
	Center.y = min(Corner1.y,Corner2.y)+ length/2;
	;
	if(num>=1){
		max(Corner1.x, Corner2.x) = max(Corner1.x, Corner2.x) + (width / num) * (num - 1);
		max(Corner1.y, Corner2.y) = max(Corner1.y, Corner2.y) + (length / num) * (num - 1);
		min(Corner1.x, Corner2.x) = min(Corner1.x, Corner2.x) - (width / num) * (num - 1);
		min(Corner1.y, Corner2.y) = min(Corner1.y, Corner2.y) - (length / num) * (num - 1);
	}
	else if(num<1){
		max(Corner1.x,Corner2.x) = max(Corner1.x,Corner2.x) - (width - width * num) / 2;
		max(Corner1.y,Corner2.y) = max(Corner1.y,Corner2.y) - (length - length * num) / 2;
		min(Corner1.x, Corner2.x) = min(Corner1.x, Corner2.x) + (width - width * num) / 2;
		min(Corner1.y,Corner2.y) = min(Corner1.y,Corner2.y) + (length - length * num) / 2;
	}
	
	/*Corner1.x = Corner1.x + (num/2) * abs(Corner1.x-Center.x);
	Corner1.y = Corner1.y + (num/2) * abs(Corner1.y-Center.y);
	Corner2.x = Corner2.x + (num/2) * abs(Corner2.x-Center.x);
	Corner2.y = Corner2.y + (num/2) * abs(Corner2.y-Center.y);*/
}