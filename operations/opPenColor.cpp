#include "opPenColor.h"
#include "opColorPalette.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opPenColor::opPenColor(controller* pCount) :operation(pCount)
{}

void opPenColor::Execute()
{

	//ColorPaletteForFillColor->Execute();

	ColorPaletteForFillColor->Execute();
	color NewColor = ColorPaletteForFillColor->GetNewColor();
	GUI* pUI = pControl->GetUI();
	pUI->setCrntDrawColor(NewColor);

}


opPenColor::~opPenColor()
{
	delete ColorPaletteForFillColor;
	ColorPaletteForFillColor = nullptr;

}