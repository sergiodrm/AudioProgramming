#pragma once

#include "AudioSource.h"
#include "World.h"
#include "InputCodes.h"

class CGameObject;

class CScene
{
public:

  CScene();

  void Init();
  void Shutdown();

  void ReceiveInputPlayer(SInputCode::EKey _key, SInputCode::EAction _action);

private:

  CGameObject* m_sourceGameObject;

  SSourceData m_sourceData;
};
