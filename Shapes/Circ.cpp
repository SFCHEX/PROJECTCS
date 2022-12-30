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

	outfile<<"Circle"<<","<<ShpGfxInfo.ID<<",";
	outfile<<Center.x<<","<<Center.y<<","<<PointR.x<<","<<PointR.y<<",";
	shape::Save(outfile);
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

ShapePoints Circ::getPoints() {
	ShapePoints CircP;
	CircP.P_num = 2;
	CircP.s_Points.resize(CircP.P_num);
	
	CircP.s_Points[0].x = this->Center.x;
	CircP.s_Points[0].y = this->Center.y;

	CircP.s_Points[1].x = this->PointR.x;
	CircP.s_Points[1].y = this->PointR.y;

	return CircP;
}

void Circ::MoveShape(Point MoveBy) {
	this->Center.x = this->Center.x + MoveBy.x;
	this->Center.y = this->Center.y + MoveBy.y;

	this->PointR.x = this->PointR.x + MoveBy.x;
	this->PointR.y = this->PointR.y + MoveBy.y;
}

void Circ::StickImageSh(GUI* pUI, string imagefile) {
	if (hasImage()) {
		double r = sqrt((Center.x - PointR.x) * (Center.x - PointR.x) + (Center.y - PointR.y) * (Center.y - PointR.y));
		double x = Center.x - (sqrt(2) / 2) * r; //the x coordinate of the image
		double y = Center.y - (sqrt(2) / 2) * r; //the y coordinate of the image 
		double wid = sqrt(2) *r; //the width of the image
		double len = sqrt(2) *r; //the length of the image
		pUI->StickImageGUI(imagefile, x, y, wid, len);
	}
}
 
void Circ::resizeSH(double num){
	if(num>=1){
		PointR.x = PointR.x + num * abs(PointR.x-Center.x);
		PointR.y = PointR.y + num * abs(PointR.y-Center.y);
	}
	else{
		PointR.x = PointR.x - num * abs(PointR.x-Center.x);
		PointR.y = PointR.y - num * abs(PointR.y-Center.y);
	}
	
	//Center.x = num * Center.x;
	//Center.y = num * Center.y;
}