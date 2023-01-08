#ifndef DEFS_H
#define DEFS_H


//This file contais some global constants and definitions to be used in the project.
enum operationType //The operations supported (you can add more if needed)
{
	DRAW_LINE,		//Draw Line
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRI,		//Draw Triangle
	DRAW_CIRC,		//Draw Circle
	DRAW_SQUARE,	//Draw Square
	DRAW_OVAL,		//Draw Oval
	DRAW_IPOLY,		//Draws Irregular Polygon
	DRAW_RPOLY,		//Draws regular Polygon
	CHNG_FILL_CLR,	//Change the filling color
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_PEN_WIDTH, //Change the pen width
	CHNG_BK_CLR,	//Change background color
	DELETE_SHAPE,	//Delete a shape(s)
	MOVE,			//Move a shape(s)
	RESIZE,			//Resize a shape(s)
	ROTATE,			//Rotate a shape(s)
	SEND_BACK,		//Send a shape to the back of all shapes
	BRNG_FRNT,		//Bring a shape to the front of all shapes
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	COPY,			//Load a graph from a file
	CUT,
	PASTE,			//Load a graph from a file
	UNDO,			//Save the whole graph to a file
	REDO,			//Save the whole graph to a file
	EXIT,			//Exit the application
	DRAG_MODE,		//Starts dragging mode
	DRAWING_AREA,	//A click on the drawing area
	SELECTION_MODE,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mod
	STICK_IMAGE,
	SCRAMBLE,
	SEND_TO_BACK,
	ZOOM,
	DO_NOTHING,
	HIDE_SHAPE,
	///TODO: Add more operation types (if needed)
};

#endif
