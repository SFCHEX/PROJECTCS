#pragma once



#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

#include <string>
#include <cmath>
#include <vector>
#include <stack>
using namespace std;

struct Point	//To be used for shapes points
{
	int x, y;
	Point operator=(const Point rhs) {
		Point Lhs = *this;
		this->x = rhs.x;
		this->y = rhs.y;
		return Lhs;
	}
	Point operator+(const Point rhs) {
		Point Lhs = *this;
		Lhs.x = Lhs.x +rhs.x;
		Lhs.y = Lhs.y +rhs.y;
		return Lhs;
	}
	Point operator-(const Point rhs) {
		Point Lhs = *this;
		Lhs.x = Lhs.x - rhs.x;
		Lhs.y = Lhs.y - rhs.y;
		return Lhs;
	}
	Point operator/(const double rhs) {
		Point Lhs = *this;
		Lhs.x = Lhs.x / rhs;
		Lhs.y = Lhs.y / rhs;
		return Lhs;
	}
	Point operator*(const double rhs) {
		Point Lhs = *this;
		Lhs.x = Lhs.x * rhs;
		Lhs.y = Lhs.y * rhs;
		return Lhs;
	}	
	Point abs(const Point rhs) {
		Point Lhs;
		Lhs.x = std::abs(rhs.x);
		Lhs.y = std::abs(rhs.y);
		return Lhs;
	}
};

struct GfxInfo	//Graphical info common for all shapes (you may add more members)
{
	color DrawClr;	//Draw color of the shape
	color FillClr;	//Fill color of the shape
	string ShapeType; //shape type is shape in string will be initialized in constructor for every shape
	int ID; // ID is unique for every shape
	bool isFilled;	//shape Filled or not
	int BorderWdth;	//Width of shape borders
	bool isSelected;	//true if the shape is selected.
	bool isHidden = false;
	int HidId;
	int GameID;
	int groupID =0; //id of the group (not zero if grouped)
};




class GUI
{
	enum GUI_MODE	//Graphical user interface mode
	{
		MODE_DRAW,	//Drawing mode (startup mode)
		MODE_PLAY	//Playing mode
	};

	enum DrawMenuIcon //The icons of the Draw menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_RECT,		//Recangle icon in menu
		ICON_CIRC,		//Circle icon in menu
		ICON_LINE,      //icon for line
		ICON_TRI,       //icon for triangle
		ICON_SQUARE,    //icon for square
		ICON_OVAL,      //icon for oval
		ICON_IPOLY,		//icon for irregular polygon
		ICON_RPOLY,		//icon for regular polygon
		ICON_STICK_IMAGE, 
		ICON_DELETE, 		//Delete icon in menu
		ICON_LOAD,		//Load icon in menu
		ICON_SAVE,		//Save icon in menu
		ICON_ROTATE,
		ICON_FILL_COLOR, //Fill color icon in menu
		ICON_PEN_COLOR,  //Pen color icon in menu
		ICON_PEN_WIDTH,  //Pen width icon in menu
		ICON_COPY,  //COPY icon in menu
		ICON_CUT,
		ICON_PASTE,  //PASTE width icon in menu
		ICON_SWITCH, //switch to play mode
		ICON_DRAG,
		ICON_RESIZE,
		ICON_UNDO,  //PASTE width icon in menu
		ICON_REDO,  //PASTE width icon in menu
		//TODO: Add more icons names here
		ICON_SCRAMBLE,
		ICON_SEND_TO_BACK,
		ICON_DUPLICATE,
		ICON_MULTI_SELECT,
		ICON_ZOOM,
		ICON_GROUP,
		ICON_UNGROUP,
		ICON_EXIT,		//Exit icon


		/// ANYTHING IN THE BOTTOM HALF OF THE TOOL BAR MUST BE PLACED UNDER THIS LINE//////////////
		/// THE ORDER IS IMPORTANT!!!!!/////////////////////////////////////////////////////////////
		 //Scrambles shapes
		ICON_TEMP,
		DRAW_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};

	enum PlayMenuIcon //The icons of the Play menu (you should add more icons)
	{
		ICON_DRAWMODE,
		ICON_MATCH,

		ICON_START_GAME,


		PLAY_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};


	GUI_MODE InterfaceMode;

	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuIconWidth;		//Width of each icon in toolbar menu
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes
	bool GeneralIsFilled;

	/// Add more members if needed

	Point* PrevPoint = new Point();
	window* pWind;
	window* pColorPaletteWindow;

public:


	GUI();

	// Input Functions  ---------------------------
	Point* PrevPrevPoint = new Point();
	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks
	string GetString() const;	 //Returns a string entered by the user
	operationType GetUseroperation() const; //Read the user click and map to an operation
	Point* GetPrevPoint() const;
	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreatePlayToolBar();	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void switchToDraw();
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	GUI_MODE CurrentMode() { return InterfaceMode; };
	// -- shapes Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const;  //Draw a rectangle
	void DrawLine(Point, Point, GfxInfo) const;
	void DrawTri(Point, Point, Point, GfxInfo) const;
	void DrawCirc(Point, Point , GfxInfo) const;
	void DrawSquare(Point, Point, GfxInfo) const;
	void DrawOval(Point, Point, GfxInfo) const;
	void DrawiPoly(vector<int>, vector<int>, GfxInfo) const;
	void DrawrPoly(vector<int>, vector<int>, GfxInfo) const;

	///Make similar functions for drawing all other shapes.

	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	void setCrntDrawColor(color c); 	//set a new drwaing color

	color getCrntFillColor() const;	//get current filling color
	void setCrntFillColor(color c);     // set a new filling color

	int getCrntPenWidth() const;		//get current pen width
	void setCrntPenWidth(int newWidth); 		//set a new pen width


	//
	//void GetColorFromColorPalette();
	////void CloseColorPaletteWindow();
	//color GetNewColor();
	void SwitchToPlayMode(window w);
	void CreatePlayModeToolBar(window & testWindow, string *MenuItems, int ItemCount, int MenuItemWidth, int MenuItemHeight);
	
	const button LeftButton = LEFT_BUTTON;
	
	// Changes the color to a new one, obtained by clicking on a color from the color palette
	void GetColorFromColorPalette(color&); 

	void switchToPlay();

	void StickImageGUI(string imagefile, double x, double y, double width, double length);
	
	bool getFillStatus();
	void setFillStatus();
	const buttonstate getClickState(int& x, int& y);	
	~GUI();
};
