#pragma once

#include "Component.h"
#include "Vec2.h"
#include "InputCodes.h"

class CMovementComponent : public CComponent
{
public:

  CMovementComponent();

  virtual void OnCreate() override;
  virtual void Update(float _deltaTime) override;


  void Jump();
  void SetControlledByPlayer(bool _process);
  void ProcessInput(SInputCode::EKey _key, SInputCode::EAction _action);
  const Vec2& GetMovementDirection() const;
  float GetSpeed() const;

private:

  Vec2 m_movementInput;
  float m_speed;
  bool m_bProcessingInput;

};

