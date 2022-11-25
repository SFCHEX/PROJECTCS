void DrawPlayModeToolBar(window & testWindow, string *MenuItems, int ItemCount, int MenuItemWidth, int MenuItemHeight){
    // Draw menu item one image at a time
	for(int i=0; i<ItemCount; i++){
		testWindow.DrawImage(MenuItems[i], i*MenuItemWidth, 0, MenuItemWidth, MenuItemHeight);
    }

	// Draw a line under the play toolbar
	testWindow.SetPen(RED, 3);
	testWindow.DrawLine(0, MenuItemHeight, testWindow.GetWidth(), MenuItemHeight);	
}
