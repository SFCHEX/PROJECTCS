#include "Rect.h"

Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{


	ShpGfxInfo.ShapeType="Rect";
	Corner1 = P1;
	Corner2 = P2;
}

Rect::~Rect(){}
//
//Point Rect::getBorders() {
//	return Corner1;
//}

string Rect::GetShapeType() const{
	return "RECT";
}
void Rect::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}

void Rect::Save(ofstream &outfile){
	outfile<<Corner1<<"\t"<<Corner2<<"\t";
}	//Save the shape parameters to the file