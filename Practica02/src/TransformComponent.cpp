#include "TransformComponent.h"

CTransformComponent::CTransformComponent()
  : Super(), m_position(), m_rotation(0.f)
{}

void CTransformComponent::Update(float _deltaTime) {}

const Vec2& CTransformComponent::GetPosition() const { return m_position; }

float CTransformComponent::GetRotation() const { return m_rotation; }

void CTransformComponent::SetPosition(Vec2 _position)
{
  m_position = _position;
}

void CTransformComponent::SetRotation(float _rotation)
{
  m_rotation = _rotation;
}


