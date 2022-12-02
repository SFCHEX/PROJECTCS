#include "opDeleteShape.h"

#include "..\Graph.h"

#inclue "..\Shape.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opDeleteShape::opDeletShape(controller *pCont):operation(pCont){}

opDeleteShape::~opDeleteShape(){}

void opDeleteShape::Excute(){
  for(int i =0; i < shapesList.size(); i++){
      if(shapesList[i]->IsSelected()){
        shapesList.erase(shapesList.begin() + i);
      }
  }
}
