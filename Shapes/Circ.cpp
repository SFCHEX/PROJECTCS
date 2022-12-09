#include "Circ.h"

Circ::Circ(Point P1, Point P2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{

	ShpGfxInfo.ShapeType="Circle";
	Center = P1;
	PointR = P2;


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
	outfile<<Center.x<<","<<Center.y<<","<<PointR.x<<","<<PointR.y<<",";
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