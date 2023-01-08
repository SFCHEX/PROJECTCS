#include "shape.h"
int shape::count =0;
shape::shape(GfxInfo shapeGfxInfo)
{ 
	imageOn=false;
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
	updateID();
	//id is added into ShpGfx info for more convenient use
}

shape::shape()
{ 
	imageOn=false;
}
 
void shape::Load(ifstream &Infile){
	int red,green,blue;
	Infile>>red;
	Infile>>green;
	Infile>>blue;

    ShpGfxInfo.DrawClr=color(red,green,blue);

	string value;
	Infile>>value;
    ShpGfxInfo.isSelected=false;
    if (value=="NO_FILL"){
        ShpGfxInfo.isFilled=false;
    }
    else{
        ShpGfxInfo.isFilled=true;
		Infile>>green;
		Infile>>blue;
        ShpGfxInfo.FillClr=color(stoi(value),green,blue);
    }
	Infile>>ShpGfxInfo.BorderWdth;
	ShpGfxInfo.isSelected=false;

}
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }



void shape::updateID(){
	ShpGfxInfo.ID=count;
	count++;
	ShpGfxInfo.HidId = count;
}

bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }

GfxInfo shape::getGfxInfo() const
{
	return ShpGfxInfo;
}

void shape::SaveColorRGB(ofstream &outfile,color RGB){

	outfile<<(int)RGB.ucRed<<" "<<(int)RGB.ucGreen<<" "<<(int)RGB.ucBlue<<" ";
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
			outfile<<"NO_FILL"<<" ";
		}		
		outfile<<it_info.BorderWdth<<endl;
}
int shape::getID() const
{
	return ShpGfxInfo.ID;
}


void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }

void shape::ChngFillClr(color Fclr)
{	
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
}
void shape::noFillColor(){

	ShpGfxInfo.isFilled = false;
}

void shape::ChngPenWidth(int c)
{
	ShpGfxInfo.BorderWdth = c;
}

void shape::StickImageSh(GUI* pUI, string imagfile){
}

bool shape::hasImage() {
	return imageOn;
}

void shape::setHasImage() {
	imageOn = true;
}

void shape::scramble(GUI* pUI)
{
}
// 
//Point shape::getBorders() {}

void shape::resizeSH(double num){}

void shape::rotateSH(){}

void shape::updateGroupId(int newGroupID){
	this->ShpGfxInfo.groupID = newGroupID;
}
int shape::getGroupId() const {
	return this->ShpGfxInfo.groupID;
}
