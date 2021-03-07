#pragma once

#include "MovementComponent.h"

class CCircleMovementComponent : public CMovementComponent
{
public:

  CCircleMovementComponent();

  virtual void Update(float _deltaTime) override;

  void SetCenter(const Vec2& _center);
  void SetRadius(float _radius);

private:

  Vec2 m_center;
  float m_radius;
};

