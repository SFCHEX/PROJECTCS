#include "Tri.h"

Tri::Tri(Point P1, Point P2, Point P3, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{

	ShpGfxInfo.ShapeType="Triangle";
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}

Tri::~Tri()
{}

void Tri::Draw(GUI* pUI) const
{
	//Call Output::DrawTri to draw a Triangle on the screen	
	pUI->DrawTri(Corner1, Corner2, Corner3, ShpGfxInfo);
}

double Tri::Area(int x1, int y1, int x2, int y2, int x3, int y3) const {
	double triarea;
	triarea = abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2);
	return triarea;
}

void Tri::Save(ofstream &outfile){
	outfile<<Corner1.x<<","<<Corner1.y<<","<<Corner2.x<<","<<Corner2.y<<","<<Corner3.x<<","<<Corner3.y<<",";

}	//Save the shape parameters to the file

bool Tri::isInside(int x, int y) const {
	double mainArea, tArea1, tArea2, tArea3;
	mainArea = Area(Corner1.x,Corner1.y, Corner2.x, Corner2.y, Corner3.x, Corner3.y);
	tArea1 = Area(x, y, Corner2.x, Corner2.y, Corner3.x, Corner3.y);
	tArea2 = Area(Corner1.x, Corner1.y, x, y, Corner3.x, Corner3.y);
	tArea3 = Area(Corner1.x, Corner1.y, Corner2.x, Corner2.y, x, y);
	return (mainArea == tArea1 + tArea2 + tArea3);
}

