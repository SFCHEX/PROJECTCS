#pragma once
#include "operation.h"
#include "opColorPalette.h"


class opPenColor : public operation
{
private:
	opColorPalette* ColorPaletteForFillColor = new opColorPalette(pControl);

public:
	opPenColor(controller* pCont);
	void Execute();

	~opPenColor();

};
