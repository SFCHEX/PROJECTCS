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
	/// Add more parameters if needed.


public:
    shape(GfxInfo shapeGfxInfo);
	virtual ~shape() {}
    void SetSelected(bool s);	//select/unselect the shape
	virtual shape* clone()=0;	//select/unselect the shape
	bool IsSelected() const;	//check whether fig is selected
	GfxInfo getGfxInfo() const;
	int getID() const;
	void updateID();
	virtual void Draw(GUI* pUI) const  = 0 ;		//Draw the shape
	void ChngDrawClr(color Dclr);	//changes the shape's drawing color
	void ChngFillClr(color Fclr);	//changes the shape's filling color
	virtual bool isInside(int x, int y) const = 0; //checks if any given point is inside a certain shape
	virtual ShapePoints getPoints() = 0; //Gets the x and y verticies for any shape
	///The following functions should be supported by the shape class
	///It should be overridden by each inherited shape
	///Decide the parameters that you should pass to each function	

	virtual void StickImageSh(GUI* pUI, string imagefile); //sticks an image to every shape

	//virtual void Rotate() = 0;	//Rotate the shape
	//virtual void Resize() = 0;	//Resize the shape
	//virtual void Move() = 0;		//Move the shape

	virtual void Save(ofstream &outfile) = 0;	//Save the shape parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the shape parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all shape info on the status bar
};

