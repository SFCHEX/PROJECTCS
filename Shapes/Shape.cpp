#include "shape.h"

int shape::count =0;
shape::shape(GfxInfo shapeGfxInfo)
{ 
	imageOn = false;
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
	updateID();
	//id is added into ShpGfx info for more convenient use
}
 
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }

void shape::updateID(){
	ShpGfxInfo.ID=count;
	count++;
}

bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }

GfxInfo shape::getGfxInfo() const
{
	return ShpGfxInfo;
}

int shape::getID() const
{
	return ShpGfxInfo.ID;
}


void shape::StickImageSh(GUI* pUI, string imagfile){
}

bool shape::hasImage() {
	return imageOn;
}

void shape::setHasImage() {
	imageOn = true;
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