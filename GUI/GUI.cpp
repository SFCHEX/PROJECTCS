#include "GUI.h"


GUI::GUI()
{
	//Initialize user interface parameters
	InterfaceMode = MODE_DRAW;

	width = 1380;
	height = 900;
	wx = 5;
	wy = 5;

	StatusBarHeight = 50;
	ToolBarHeight = 100;
	MenuIconWidth = 80;

	DrawColor = BLUE;	//default Drawing color
	FillColor = GREEN;	//default Filling color
	MsgColor = BLACK;		//Messages color
	BkGrndColor = WHITE;	//Background color
	HighlightColor = MAGENTA;	//This color should NOT be used to draw shapes. use if for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3;	//default width of the shapes frames
	GeneralIsFilled = false;


	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");
	PrevPoint->x = 0; PrevPoint->y = 0;
	CreateDrawToolBar();
	CreateStatusBar();

}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetString() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if( Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation() const
{
	PrevPrevPoint->x = PrevPoint->x ; PrevPrevPoint->y = PrevPoint->y;

	int x, y;
	//pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	pWind->WaitMouseClick(x, y);




	if (InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the first Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==

			int ClickedIconOrder = (x / MenuIconWidth);

			if (y <= ToolBarHeight/2) {
				ClickedIconOrder = ClickedIconOrder;
			}
			else {
				ClickedIconOrder = ClickedIconOrder + 17;
			}
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder)
			{
			case ICON_RECT: return DRAW_RECT;
			case ICON_COPY: return COPY;
			case ICON_PASTE: return PASTE;
			case ICON_CIRC: return DRAW_CIRC;
			case ICON_LINE: return DRAW_LINE;
			case ICON_TRI : return DRAW_TRI;
			case ICON_SQUARE: return DRAW_SQUARE;
			case ICON_OVAL: return DRAW_OVAL;
			case ICON_IPOLY: return DRAW_IPOLY;
			case ICON_RPOLY: return DRAW_RPOLY;
			case ICON_DELETE: return DELETE_SHAPE;
			case ICON_LOAD: return LOAD;
			case ICON_SAVE: return SAVE;
			case ICON_SWITCH: return TO_PLAY;
			case ICON_FILL_COLOR: return CHNG_FILL_CLR;
			case ICON_PEN_COLOR: return CHNG_DRAW_CLR;
			case ICON_PEN_WIDTH: return CHNG_PEN_WIDTH;
			case ICON_EXIT: return EXIT;
			case ICON_SELECT: return SELECTION_MODE;
			case ICON_TEMP: return DO_NOTHING;
			case ICON_UNDO: return UNDO;
			case ICON_REDO: return REDO;
			case ICON_STICK_IMAGE: return STICK_IMAGE;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}


		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		//[1] If user clicks on the first Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==

			int ClickedIconOrder = (x / MenuIconWidth);

			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder)
			{
			case ICON_ROTATE: return ROTATE;
			case ICON_TEMP: return DO_NOTHING;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}


		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return DRAWING_AREA; //MAYBE CHANGED TO PLAYING_AREA IF NEEDED
		}

		//[3] User clicks on the status bar
		return STATUS;
		
		//return TO_PLAY;	//just for now. This should be updated
	}

}
Point* GUI::GetPrevPoint() const
{
	return this->PrevPoint;
}
////////////////////////////////////////////////////



//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar()
{
	InterfaceMode = MODE_DRAW;
	
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu icon
	//To control the order of these images in the menu,
	//reoder them in UI_Info.h ==> enum DrawMenuIcon
	string MenuIconImages[DRAW_ICON_COUNT];
	MenuIconImages[ICON_RECT] = "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImages[ICON_CIRC] = "images\\MenuIcons\\Menu_Circ.jpg";
	MenuIconImages[ICON_LINE] = "images\\MenuIcons\\Menu_Line.jpg";
	MenuIconImages[ICON_TRI]  = "images\\MenuIcons\\Menu_Tri.jpg";
	MenuIconImages[ICON_SQUARE] = "images\\MenuIcons\\Menu_Square.jpg";
	MenuIconImages[ICON_OVAL] = "images\\MenuIcons\\Menu_Oval.jpg";
	MenuIconImages[ICON_IPOLY] = "images\\MenuIcons\\Menu_iPoly.jpg";
	MenuIconImages[ICON_RPOLY] = "images\\MenuIcons\\Menu_rPoly.jpg";
	MenuIconImages[ICON_DELETE] = "images\\MenuIcons\\Menu_Delete.jpg";
	MenuIconImages[ICON_LOAD] = "images\\MenuIcons\\Menu_Load.jpg";
	MenuIconImages[ICON_SAVE] = "images\\MenuIcons\\Menu_Save.jpg";
	MenuIconImages[ICON_FILL_COLOR] = "images\\MenuIcons\\Menu_Fill_Color.jpg";
	MenuIconImages[ICON_PEN_COLOR] = "images\\MenuIcons\\Menu_Pen_Color.jpg";
	MenuIconImages[ICON_PEN_WIDTH] = "images\\MenuIcons\\Menu_Pen_Width.jpg";
	MenuIconImages[ICON_COPY] = "images\\MenuIcons\\Menu_Copy.jpg";
	MenuIconImages[ICON_STICK_IMAGE] = "images\\MenuIcons\\Menu_Stick.jpg";
	MenuIconImages[ICON_PASTE] = "images\\MenuIcons\\Menu_Paste.jpg";
	MenuIconImages[ICON_UNDO] = "images\\MenuIcons\\Menu_Undo.jpg";
	MenuIconImages[ICON_REDO] = "images\\MenuIcons\\Menu_Redo.jpg";
	MenuIconImages[ICON_EXIT] = "images\\MenuIcons\\Menu_Exit.jpg";
	MenuIconImages[ICON_SELECT] = "images\\MenuIcons\\Menu_Select.jpg";
	MenuIconImages[ICON_TEMP] = "images\\MenuIcons\\Menu_Temp.jpg";
	MenuIconImages[ICON_SWITCH] = "images\\MenuIcons\\Menu_Switch.jpg";

	//TODO: Prepare images for each menu icon and add it to the list

	//Draw menu icon one image at a time
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		if (i < 17) {
			pWind->DrawImage(MenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight / 2);
		}
		else {
			pWind->DrawImage(MenuIconImages[i], (i-17) * MenuIconWidth, ToolBarHeight / 2, MenuIconWidth, ToolBarHeight / 2);
		}



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar()
{
	InterfaceMode = MODE_PLAY;
	string PlayMenuIconImages[1];//string PlayMenuIconImages[PLAY_ICON_COUNT];//
	PlayMenuIconImages[0]="images\\PlayMenuIcons\\PlayMenu_Rotate.jpg";//PlayMenuIconImages[ROTATE]="images\\PlayMenuIcons\\PlayMenu_Rotate.jpg"

	for (int i = 0; i < PLAY_ICON_COUNT; i++)
		pWind->DrawImage(PlayMenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight / 2);
	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return DrawColor;
}
void GUI::setCrntDrawColor(color c) 	//set a new drwawing color
{
	DrawColor = c;
}

//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return FillColor;
}
void GUI::setCrntFillColor(color c) 	//set a new filling color
{
	FillColor = c;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return PenWidth;
}
void GUI::setCrntPenWidth(int newWidth) 		//set a new pen width
{
	PenWidth = newWidth;
}


//======================================================================================//
//                         General fill color setter and getter                         //
//======================================================================================//

bool GUI::getFillStatus()
{
	return GeneralIsFilled;
}

void GUI::setFillStatus()
{
	GeneralIsFilled = true;
}
//======================================================================================//
//                              Color Paletee                                           //
//======================================================================================//

void GUI::GetColorFromColorPalette(color& c)
{
	int widthForColorPalette = 700;
	int heightForColorPalette = 700;
	int startx = 200;
	int starty = 100;
	int x, y;

	pColorPaletteWindow = CreateWind(widthForColorPalette, heightForColorPalette, startx, starty);
	pColorPaletteWindow->ChangeTitle("Color Palette");
	image ColorPalette("images\\MenuIcons\\Color_Palette.jpg", JPEG);
	pColorPaletteWindow->DrawImage(ColorPalette, 0, 0, 700, 700);

	pColorPaletteWindow->WaitMouseClick(x, y);
	c = pColorPaletteWindow->GetColor(x, y);	
	delete pColorPaletteWindow;
	pColorPaletteWindow = nullptr;

}

//color GUI::GetNewColor()
//{
//	//GetColorFromColorPalette();
//	int x, y;
//	pColorPaletteWindow->WaitMouseClick(x, y);
//	color NewColor = pColorPaletteWindow->GetColor(x, y);
//	return NewColor;
//	/*delete pColorPaletteWindow;
//	pColorPaletteWindow = nullptr;*/
//}

//======================================================================================//
//								SWITCH FUNCTION								//
//======================================================================================//
void GUI::switchToPlay()
{
	
	////pGr->Save(); //saves all shapes (SAIF SHOULD DO THIS LINE)
	//saves the shapes
	ClearStatusBar();
	////clear status bar
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, 0, width, height);
	////clear the window
	CreatePlayToolBar();
	

	

}

//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const
{
	color DrawingClr;
	if (RectGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}

void GUI::DrawLine(Point p1, Point p2, GfxInfo LineGfxInfo) const {
	color DrawingClr;
	if (LineGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind ->SetPen(DrawingClr, LineGfxInfo.BorderWdth);

	drawstyle style;
	if (LineGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(LineGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawLine(p1.x, p1.y, p2.x, p2.y, style);

}

void GUI::DrawTri(Point p1, Point p2, Point p3, GfxInfo TriGfxInfo) const {
	color DrawingClr;
	if (TriGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth);

	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, style);
}

void GUI::DrawCirc(Point P1, Point P2, GfxInfo CircGfxInfo) const {
	int rad;
	color DrawingClr;
	if (CircGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = CircGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircGfxInfo.BorderWdth);

	drawstyle style;
	if (CircGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircGfxInfo.FillClr);
	}
	else
		style = FRAME;
	rad = int(sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2)));
	pWind->DrawCircle(P1.x, P1.y, rad, style);
}

void GUI::DrawSquare(Point P1, Point P2, GfxInfo SquareGfxInfo) const
{
	color DrawingClr;
	if (SquareGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, SquareGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}
void GUI::DrawOval(Point P1, Point P2, GfxInfo OvalGfxInfo) const
{
	color DrawingClr;
	if (OvalGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = OvalGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, OvalGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (OvalGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(OvalGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);

}

void GUI::DrawiPoly(vector<int> vx, vector<int> vy, GfxInfo iPolyGfxInfo) const {
	color DrawingClr;
	if (iPolyGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = iPolyGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, iPolyGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (iPolyGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(iPolyGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int* ax = &vx[0];
	int* ay = &vy[0];
	int asize = size(vx);
	pWind->DrawPolygon(ax, ay, asize, style);
}
void GUI::DrawrPoly(vector<int> vx, vector<int> vy, GfxInfo rPolyGfxInfo) const {
	color DrawingClr;
	if (rPolyGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = rPolyGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, rPolyGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (rPolyGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(rPolyGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int* ax = &vx[0];
	int* ay = &vy[0];
	int asize = size(vx);
	pWind->DrawPolygon(ax, ay, asize, style);
}

void GUI::StickImageGUI(string imagefile, double x, double y, double width, double length){
	pWind->DrawImage(imagefile,x,y,width,length);
}


buttonstate const GUI::getClickState(int& x, int& y)  {
	return pWind->GetButtonState(LeftButton, x, y);
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
	delete PrevPoint;
}

