#include "Oval.h"

Oval::Oval(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ShpGfxInfo.ShapeType="Oval";
	Corner1 = P1;
	Corner2 = P2;



}


shape* Oval::clone(){
	shape* newShape=new Oval(*this);

	newShape->updateID(); return newShape;

}	
Oval::~Oval()
{}

void Oval::Draw(GUI* pUI) const
{
	//Call Output::DrawOval to draw a Ovalangle on the screen	
	pUI->DrawOval(Corner1, Corner2, ShpGfxInfo);
}
void Oval::Save(ofstream &outfile){
	outfile<<Corner1.x<<","<<Corner1.y<<","<<Corner2.x<<","<<Corner2.y<<",";
}	//Save the shape parameters to the file

bool Oval::isInside(int x, int y) const {
	double radX = abs((Corner1.x - Corner2.x)/2);
	double radY = abs((Corner1.y - Corner2.y)/2);
	double centX = abs((Corner1.x + Corner2.x)/2);
	double centY = abs((Corner1.y + Corner2.y)/2);

	return (((pow((x - centX), 2)) / (pow(radX, 2))) + ((pow((y - centY), 2)) / (pow(radY, 2)))) <= 1;
}

void Oval::StickImageSh(GUI* pUI, string imagefile) {
	if (hasImage()){
		double x = min(Corner1.x, Corner2.x); //the x coordinate of the image
		double y = abs((Corner1.y + Corner2.y) / 2) - abs((Corner1.y - Corner2.y) / 4); //the y coordinate of the image //NEEDS UPDATE
		double wid = abs(Corner2.x - Corner1.x); //the width of the image
		double len = abs(Corner2.y - Corner1.y)/2; //the length of the image
		pUI->StickImageGUI(imagefile, x, y, wid, len);
		setHasImage();
	}
}
ShapePoints Oval::getPoints() {
	ShapePoints OvalP;
	OvalP.P_num = 2;
	OvalP.s_Points.resize(OvalP.P_num);

	OvalP.s_Points[0].x = this->Corner1.x;
	OvalP.s_Points[0].y = this->Corner1.y;

	OvalP.s_Points[1].x = this->Corner2.x;
	OvalP.s_Points[1].y = this->Corner2.y;

	return OvalP;
}