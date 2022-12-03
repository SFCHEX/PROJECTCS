#pragma once

#include "operation.h"
class opColorPalette : public operation
{
private:
	int width, height;
	int wx, wy;

	window* pColorPaletteWindow;

public:
	opColorPalette(controller* pCont);
	virtual void Execute();

	// returns a color when the user click on the palette
	color GetNewColor();

	virtual ~opColorPalette();

};

