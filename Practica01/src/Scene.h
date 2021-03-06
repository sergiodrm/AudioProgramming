#pragma once

#include "World.h"
#include "InputCodes.h"

class CScene
{
public:

  CScene();

  void Init();
  void Shutdown();

  void ReceiveInputPlayer(SInputCode::EKey _key, SInputCode::EAction _action);

private:

  CGameObject* m_playerGameObject;
};

