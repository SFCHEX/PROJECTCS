#include "CMUgraphics.h"
#include <iostream>
#include"DrawPlayModeToolBar.h"

void switchToPlayMode(window w){
    w.SetPen(WHITE,1);
    w.SetBrush(WHITE);
    w.DrawRectangle(0,0,w.GetWidth,w.GetHeight,w.GetWidth,w.GetHeight);

    const int count = 5;
	  const int menuHeight = 80,  menuItemWidth = 50;

	  string MenuIconsPaths[count];	
	  MenuIconsPaths[0] = "";
	  MenuIconsPaths[1] = "";
	  MenuIconsPaths[2] = "";
	  MenuIconsPaths[3] = "";
  	MenuIconsPaths[4] = "";

    DrawPlayModeToolBar(w, MenuIconsPaths, count, menuItemWidth, menuHeight)
}

