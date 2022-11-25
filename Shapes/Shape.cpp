#include "shape.h"

int shape::count =0;
shape::shape(GfxInfo shapeGfxInfo)
{ 
	count++;
	ID=count;
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
}
 
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }

bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }

int shape::getID() const
{
	return ID;
}

GfxInfo shape::getGfxInfo() const
{
	return ShpGfxInfo;
}


void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }

void shape::ChngFillClr(color Fclr)
{	
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
}

// 
//Point shape::getBorders() {}