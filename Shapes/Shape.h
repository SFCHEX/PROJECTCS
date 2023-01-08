#pragma once
#include <fstream>
#include "..\defs.h"
#include "..\GUI\GUI.h"
#include <vector>
struct ShapePoints {
	vector<Point> s_Points;
	int P_num;
};

//Base class for all shapes
class shape
{
protected:
	
	GfxInfo ShpGfxInfo;	//shape graphis info
	static int count; //to create unique ID's for each object which will be stored in gfxinfo
	bool isCard = false;
    void SaveColorRGB(ofstream &outfile,color RGB);
	/// Add more parameters if needed.
	int groupID = 0;
private:
	bool imageOn;

public:
    shape(GfxInfo shapeGfxInfo);
    shape();
	virtual ~shape() {}
    void SetSelected(bool s);	//select/unselect the shape
	void noFillColor();
	virtual shape* clone()=0;	//select/unselect the shape
	bool IsSelected() const;	//check whether fig is selected
	GfxInfo getGfxInfo() const;
	int getID() const;
	void updateID();
	virtual void Draw(GUI* pUI) const  = 0 ;		//Draw the shape
	void ChngDrawClr(color Dclr);	//changes the shape's drawing color
	void ChngFillClr(color Fclr);	//changes the shape's filling color
	void ChngPenWidth(int);
	virtual bool isInside(int x, int y) const = 0; //checks if any given point is inside a certain shape
	virtual ShapePoints getPoints() = 0; //Gets the x and y verticies for any shape
	virtual void MoveShape(Point pMove) = 0;
	virtual Point HideShape(Point DxDy) = 0;
	///The following functions should be supported by the shape class
	///It should be overridden by each inherited shape

	///Decide the parameters that you should pass to each function	
	virtual void sethideID(int) {};
	virtual bool hasImage();
	virtual void StickImageSh(GUI* pUI, string imagefile); //sticks an image to every shape
	virtual void setHasImage();
	virtual void scramble(GUI* pUI);
	virtual bool isShpHidden() { return this->ShpGfxInfo.isHidden; };
	virtual bool isaCard() { return this->isCard; };
	virtual void Zoom(double) = 0;
	virtual void unHideAll() { ShpGfxInfo.isHidden = false; }
	//virtual void Rotate() = 0;	//Rotate the shape
	//virtual void Resize() = 0;	//Resize the shape
	//virtual void Move() = 0;		//Move the shape

	virtual void Save(ofstream &outfile);	//Save the shape parameters to the file
	virtual void Load(ifstream &Infile) ;	//Load the shape parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all shape info on the status bar

	virtual void resizeSH(double num);
	virtual void rotateSH();

	void updateGroupId(int);
	int getGroupId() const;
};

