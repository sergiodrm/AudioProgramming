#pragma once

#include "Component.h"

class CAudioListenerComponent : public CComponent
{
public:

  CAudioListenerComponent();

  virtual void Update(float _deltaTime) override;

  void ActiveListener();
  void DeactiveListener();
  inline bool IsListenerActive() const { return m_listenerActive; }

private:

  bool m_listenerActive;

};

