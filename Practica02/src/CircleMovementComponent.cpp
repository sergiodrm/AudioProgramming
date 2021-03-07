#include "CircleMovementComponent.h"


#include "GameObject.h"
#include "TimeManager.h"
#include "TransformComponent.h"

CCircleMovementComponent::CCircleMovementComponent()
  : m_center(0.f, 0.f), m_radius(200.f) {}

void CCircleMovementComponent::Update(float _deltaTime)
{
  // Don't call super Update: undesired behavior

  if (IsActive())
  {
    float time = static_cast<float>(CTimeManager::GetTimer().GetTotalSeconds());
    float x = m_center.GetX() + m_radius * cosf(time);
    float y = m_center.GetY() + m_radius * sinf(time);
    GetOwner()->GetComponent<CTransformComponent>()->SetPosition(Vec2(x, y));
  }
}

void CCircleMovementComponent::SetCenter(const Vec2& _center) { m_center = _center; }
void CCircleMovementComponent::SetRadius(float _radius) { m_radius = _radius; }
