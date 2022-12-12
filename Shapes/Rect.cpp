#include "Rect.h"

Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{


	Corner1 = P1;
	Corner2 = P2;

}

Rect::~Rect(){}
//
//Point Rect::getBorders() {
//	return Corner1;
//}


shape* Rect::clone(){
	shape* newShape=new Rect(*this);

	newShape->updateID(); return newShape;
}	
void Rect::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}

void Rect::Save(ofstream &outfile){

	outfile<<"Rect"<<","<<ShpGfxInfo.ID<<",";
	outfile<<Corner1.x<<","<<Corner1.y<<","<<Corner2.x<<","<<Corner2.y<<",";
	shape::Save(outfile);
}	//Save the shape parameters to the file

bool Rect::isInside(int x, int y) const {
	return((x <= max(Corner1.x, Corner2.x)) && (y <= max(Corner1.y, Corner2.y)) && (x >= min(Corner1.x, Corner2.x)) && (y >= min(Corner1.y, Corner2.y)));
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