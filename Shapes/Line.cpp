#include "Line.h"

Line::Line(Point p1, Point p2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{


	ShpGfxInfo.ShapeType="Line";
	End1 = p1;
	End2 = p2;
}

Line::~Line() {}

void Line::Draw(GUI* pUI) const
{
	pUI->DrawLine(End1, End2, ShpGfxInfo);
}
void Line::Save(ofstream &outfile){
	outfile<<End1.x<<"\t"<<End1.y<<"\t"<<End1.x<<"\t"<<End1.y<<"\t";
}	//Save the shape parameters to the file
