#include "Line.h"

Line::Line(Point p1, Point p2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{


	ShpGfxInfo.ShapeType="Line";
	End1 = p1;
	End2 = p2;

	ShpGfxInfo.Points={End1,End2};
}

Line::~Line() {}

void Line::Draw(GUI* pUI) const
{
	pUI->DrawLine(End1, End2, ShpGfxInfo);
}
void Line::Save(ofstream &outfile){
	outfile<<End1.x<<","<<End1.y<<","<<End2.x<<","<<End2.y<<",";
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