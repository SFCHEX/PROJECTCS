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

shape* Tri::clone(){
	shape* newShape= new Tri(*this);
	newShape->updateID(); return newShape;
}



bool Tri::isInside(int x, int y) const
{
	int num = 3;
	int i, j, c = 0;
	int pVectX[3] = { Corner1.x, Corner2.x, Corner3.x };
	int pVectY[3] = { Corner1.y, Corner2.y, Corner3.y };
	for (i = 0, j = num - 1; i < num; j = i++) {
		if (((pVectY[i] > y) != (pVectY[j] > y)) &&
			(x < (pVectX[j] - pVectX[i]) * (y - pVectY[i]) / (pVectY[j] - pVectY[i]) + pVectX[i]))
			c = !c;
	}
	return c;
}

void Tri::StickImageSh(GUI* pUI, string imagefile) {
	double centroidx = (Corner1.x + Corner2.x + Corner3.x) / 3;
	double centroidy = (Corner1.y + Corner2.y + Corner3.y) / 3;
	double x = centroidx - 40;
	double y = centroidy - 40;
	double len = 100;
	double wid = 100;
	pUI->StickImageGUI(imagefile, x, y, wid, len);
	setHasImage();
}


ShapePoints Tri::getPoints() {
	ShapePoints TriP;
	TriP.P_num = 3;
	TriP.s_Points.resize(TriP.P_num);

	TriP.s_Points[0].x = this->Corner1.x;
	TriP.s_Points[0].y = this->Corner1.y;

	TriP.s_Points[1].x = this->Corner2.x;
	TriP.s_Points[1].y = this->Corner2.y;

	TriP.s_Points[2].x = this->Corner3.x;
	TriP.s_Points[2].y = this->Corner3.y;

	return TriP;
}