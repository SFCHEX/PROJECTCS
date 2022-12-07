#include "opStickImage.h"

#include "..\Shapes\Graph.h"

#include "..\Shapes\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opStickImage::opStickImage(controller * pCont):operation(pCont){}

opStickImage::~opStickImage(){}

void opStickImage::Execute(){
  Graph* pGr = pControl->getpUI();
  pGr->StickImage();
}
