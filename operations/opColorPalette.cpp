#include "opColorPalette.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"

opColorPalette::opColorPalette(controller* pCount) :operation(pCount)
{}




color opColorPalette::GetNewColor()
{
	int x, y;
	pColorPaletteWindow->WaitMouseClick(x, y);
	color NewColor = pColorPaletteWindow->GetColor(x, y);
	return NewColor;
}




void opColorPalette::Execute()
{
	width = 700;
	height = 700;
	wx = 200;
	wy = 100;

	GUI* pUI = pControl->GetUI();
	pColorPaletteWindow = pUI->CreateWind(width, height, wx, wy);
	pColorPaletteWindow->ChangeTitle("Color Palette");
	image ColorPalette("images\\MenuIcons\\Color_Palette.jpg", JPEG);

	pColorPaletteWindow->DrawImage(ColorPalette, 0, 0, 700, 700);
	

}




opColorPalette::~opColorPalette()
{
	delete pColorPaletteWindow;
	pColorPaletteWindow = nullptr;
}