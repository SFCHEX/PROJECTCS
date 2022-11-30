#include "Circ.h"

Circ::Circ(Point P1, Point P2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{

	ShpGfxInfo.ShapeType="Circ";
	Center = P1;
	PointR = P2;


}

Circ::~Circ()
{}

void Circ::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawCirc(Center, PointR, ShpGfxInfo);
}

void Circ::Save(ofstream &outfile){
	outfile<<Center.x<<Center.y<<"\t"<<PointR.x<<PointR.y<<"\t";
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