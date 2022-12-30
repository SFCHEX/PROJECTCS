#include "Rect.h"

Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{


	ShpGfxInfo.ShapeType="Rectangle";
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

void Rect::StickImageSh(GUI* pUI, string imagefile){
	if (hasImage()) {
		double x = min(Corner1.x, Corner2.x); //the x coordinate of the image
		double y = min(Corner1.y, Corner2.y); //the y coordinate of the image 
		double wid = abs(Corner2.x - Corner1.x); //the width of the image
		double len = abs(Corner2.y - Corner1.y); //the length of the image
		pUI->StickImageGUI(imagefile, x, y, wid, len);
		setHasImage();
	}
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

void Rect::MoveShape(Point MoveBy) {
	this->Corner1.x = this->Corner1.x + MoveBy.x;
	this->Corner1.y = this->Corner1.y + MoveBy.y;

	this->Corner2.x = this->Corner2.x + MoveBy.x;
	this->Corner2.y = this->Corner2.y + MoveBy.y;
}
void Rect::resizeSH(double num){
	Point Center;
	double width = abs(Corner1.x - Corner2.x);
	double length = abs(Corner1.y - Corner2.y);
	Center.x = min(Corner1.x,Corner2.x)+ (width/2);
	Center.y = min(Corner1.y,Corner2.y)+ (length/2);
	
	if(num>=1){
		max(Corner1.x, Corner2.x) = max(Corner1.x, Corner2.x) + (width / num) * (num - 1);
		max(Corner1.y, Corner2.y) = max(Corner1.y, Corner2.y) + (length / num) * (num - 1);
		min(Corner1.x, Corner2.x) = min(Corner1.x, Corner2.x) - (width / num) * (num - 1);
		min(Corner1.y, Corner2.y) = min(Corner1.y, Corner2.y) - (length / num) * (num - 1);
	}
	else if(num<1){
		max(Corner1.x,Corner2.x) = max(Corner1.x,Corner2.x) - (width - width * num) / 2;
		max(Corner1.y,Corner2.y) = max(Corner1.y,Corner2.y) - (length - length * num) / 2;
		min(Corner1.x, Corner2.x) = min(Corner1.x, Corner2.x) + (width - width * num) / 2;
		min(Corner1.y,Corner2.y) = min(Corner1.y,Corner2.y) + (length - length * num) / 2;
	}
}