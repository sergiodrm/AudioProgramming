#pragma once

#include "Component.h"
#include "Vec2.h"

class CTransformComponent : public CComponent
{
public:

  CTransformComponent();

  virtual void Update(float _deltaTime) override;
  const Vec2& GetPosition() const;
  float GetRotation() const;
  void SetPosition(Vec2 _position);
  void SetRotation(float _rotation);

protected:

  Vec2 m_position;
  float m_rotation;
};

