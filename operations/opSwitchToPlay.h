#pragma once
#include "operation.h"

class opSwitchToPlay : public operation{
public:
  opSwitchToPlay(controller *pCont);
  virtual ~opSwitchToPlay();
  virtual void Execute();
};
