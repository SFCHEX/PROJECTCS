#include "shape.h"

int shape::count =0;
shape::shape(GfxInfo shapeGfxInfo)
{ 
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

void shape::SaveColorRGB(ofstream &outfile,color RGB){

	outfile<<(int)RGB.ucRed<<","<<(int)RGB.ucGreen<<","<<(int)RGB.ucBlue<<",";
}

void shape::Save(ofstream &outfile)
{

		GfxInfo it_info = ShpGfxInfo;
		SaveColorRGB(outfile,it_info.DrawClr);
		//if condition for if there is no fill color
		if (it_info.isFilled)
		{
			SaveColorRGB(outfile,it_info.FillClr);
		}
		else
		{
			outfile<<"NO_FILL"<<",";
		}		
		outfile<<it_info.BorderWdth<<endl;
}
int shape::getID() const
{
	return ShpGfxInfo.ID;
}

bool shape::hasImage(){
	return Image;
}

void shape::setHasImage(){
	Image = true;
}
void shape::StickImageSh(GUI* pUI, string imagfile){
	
}

void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }

void shape::ChngFillClr(color Fclr)
{	
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
}

void shape::ChngPenWidth(int c)
{
	ShpGfxInfo.BorderWdth = c;
}

// 
//Point shape::getBorders() {}