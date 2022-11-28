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


}
Square::~Square(){}

void Square::Draw(GUI* pUI) const {
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}

void Square::Save(ofstream &outfile){
	outfile << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t";
}	//Save the shape parameters to the file