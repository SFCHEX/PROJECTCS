#include "Line.h"
Line::Line(Point p1, Point p2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{


	End1 = p1;
	End2 = p2;


}

void Line::Load(ifstream &Infile){
	Infile>>ShpGfxInfo.ID;
	Point P1,P2;
	Infile>>P1.x;
	Infile>>P1.y;
	Infile>>P2.x;
	Infile>>P2.y;
	ShpGfxInfo.ShapeType="Line";
	End1= P1;
	End2= P2;
	shape::Load(Infile);
}




Line::Line(){
}

shape* Line::clone(){
	shape* newShape=new Line(*this);

	newShape->updateID(); return newShape;


}
Line::~Line() {}

void Line::Draw(GUI* pUI) const
{
	pUI->DrawLine(End1, End2, ShpGfxInfo);
}
void Line::Save(ofstream &outfile){

	outfile<<"Line"<<" "<<ShpGfxInfo.ID<<" ";
	outfile<<End1.x<<" "<<End1.y<<" "<<End2.x<<" "<<End2.y<<" ";
	shape::Save(outfile);
}	//Save the shape parameters to the file

bool Line::isInside(int x, int y) const{
	if (x <= max(End1.x, End2.x) && y <= max(End1.y, End2.y) && x >= min(End1.x, End2.x) && y >= min(End1.y, End2.y)){ //checks if x and y are within line borders.
		double slope;
		if ((End2.x - End1.x) != 0) {//for any line (sloped or horizontal)
			slope = (End2.y - End1.y) / (End2.x - End1.x);
		}
		else { //for a perfectly vertical line
			if (End1.x != x) { //x needs to be the same else its not on the line
				return false;
			}
			else {
				return (abs(End1.y - End2.y) == (abs(End1.y - y) + abs(End2.y - y)));
			}
		}
		if (slope == 0) { //check for perfectly horizontal
			return (abs(End1.x - End2.x) == (abs(End1.x - x) + abs(End2.x - x)));
		}
		else {
			return ((y - End1.y) == (slope * (x - End1.x))); //any point on the line should satisfy the normal line equation (this is another way of writing y=mx+c)
		}
	}
	else {
		return false;
	}
}

ShapePoints Line::getPoints() {
	ShapePoints LineP;
	LineP.P_num = 2;
	LineP.s_Points.resize(LineP.P_num);

	LineP.s_Points[0].x = this->End1.x;
	LineP.s_Points[0].y = this->End1.y;

	LineP.s_Points[1].x = this->End2.x;
	LineP.s_Points[1].y = this->End2.y;

	return LineP;
}

void Line::MoveShape(Point MoveBy) {
	this->End1.x = this->End1.x + MoveBy.x;
	this->End1.y = this->End1.y + MoveBy.y;

	this->End2.x = this->End2.x + MoveBy.x;
	this->End2.y = this->End2.y + MoveBy.y;
}

void Line::scramble(GUI* pUI)
{	 
	int diff_x = abs(End1.x - End2.x);
	int diff_y = abs(End1.y - End2.y);	
	End1.x = rand() % 1300 + 1;
	End1.y = 50 + rand() % 500;
	End2.x = End1.x + diff_x;
	End2.y = End1.y + diff_y;

	string msg = "(" + to_string(End1.x) + ", " + to_string(End1.y) + " ) ( " + to_string(End2.x) + ", " + to_string(End2.y) + ")";
	pUI->PrintMessage(msg);
}
void Line::resizeSH(double n) {
	Point Center;
	double width = abs(End1.x - End2.x);
	double length = abs(End1.y - End2.y);
	Center.x = min(End1.x, End2.x) + width / 2;
	Center.y = min(End1.y, End2.y) + length / 2; double t1x = End1.x;
	double t1y = End1.y;
	double t2x = End2.x;
	double t2y = End2.y;


	End1.x = (n *t1x) - (n *Center.x) + Center.x;
	End1.y = (n * t1y) - (n *Center.y) + Center.y;
	End2.x = (n * t2x) - (n *Center.x) + Center.x;
	End2.y = (n * t2y) - (n * Center.y) + Center.y;
}
void Line::rotateSH() {
	Point Center;
	double width = abs(End1.x - End2.x);
	double length = abs(End1.y - End2.y);
	Center.x = min(End1.x, End2.x) + width / 2;
	Center.y = min(End1.y, End2.y) + length / 2;

	double t1x = End1.x;
	double t1y = End1.y;
	double t2x = End2.x;
	double t2y = End2.y;
	End1.x = -t1y + (Center.x) + Center.y;
	End1.y = t1x -(Center.x) + Center.y;
	End2.x = -t2y + (Center.x) + Center.y;
	End2.y = t2x -(Center.x) + Center.y;
}

Point Line::HideShape(Point DxDy) {
	if (!ShpGfxInfo.isHidden) {

		ShpGfxInfo.isHidden = true;
		Point Shp_dxdy;
		Point max_xy, min_xy, v_Center;
		double div_scale, ratX, ratY;

		max_xy = End1;
		min_xy = End2;
		v_Center = (max_xy + min_xy) / 2;

		Shp_dxdy = Shp_dxdy.abs(max_xy - min_xy);
		ratX = (double)DxDy.x / (double)Shp_dxdy.x;
		ratY = (double)DxDy.y / (double)Shp_dxdy.y;
		div_scale = min(ratX, ratY);
		(div_scale >= 1) ? div_scale = 1 : div_scale = div_scale - 0.1;
		this->resizeSH(div_scale);
		return (v_Center - (DxDy / 2));
	}
}
void Line::Zoom(double Zf) {
	Point max_xy, min_xy, v_Center, CanvasCenter, Diff;
	CanvasCenter.x = 690; 	CanvasCenter.y = 375;
	max_xy = End1;
	min_xy = End2;
	v_Center = (max_xy + min_xy) / 2;

	if (Zf > 1) {
		Diff = (v_Center - CanvasCenter) * (Zf - 1);
		Diff = Diff / 1;
	}
	else {
		Diff = (v_Center - CanvasCenter);
		Diff = Diff * (-Zf / 1.0);

	}
	this->MoveShape(Diff);
	this->resizeSH(Zf);
}