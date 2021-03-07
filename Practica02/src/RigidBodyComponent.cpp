#include "RigidBodyComponent.h"

#include "GameObject.h"
#include "PhysicsEngine.h"
#include "TransformComponent.h"
#include "Collider.h"

#define COLLISION_DEBUG 0

#if COLLISION_DEBUG
#include "RenderEngine.h"
#endif

CRigidBodyComponent::CRigidBodyComponent()
  : m_collider(nullptr)
{}

void CRigidBodyComponent::Update(float _deltaTime)
{
  if (IsActive() && IsPhysicsActived())
  {
    static float fallingTime = _deltaTime;
    Vec2 currentPosition = GetCollider()->GetPosition();
    Vec2 nextPosition = currentPosition + Vec2(0.f, CPhysicsEngine::GetInstance().GetGravity() * fallingTime * fallingTime) + m_velocityImpulse * _deltaTime;
    GetCollider()->SetPosition(nextPosition);
    if (CPhysicsEngine::GetInstance().CheckStaticCollision(GetCollider()))
    {
      fallingTime = _deltaTime;
      GetCollider()->SetPosition(currentPosition);
      m_velocityImpulse = Vec2();
    }
    else
    {
      fallingTime += _deltaTime;
      GetOwner()->GetComponent<CTransformComponent>()->SetPosition(nextPosition);
    }
  }
}

void CRigidBodyComponent::OnDestroy()
{
  CPhysicsEngine::GetInstance().EraseRigidBody(this);
}

void CRigidBodyComponent::CreateCollider(EColliderType _type, EColliderStatus _status, const Vec2& _position, const Vec2& _size)
{
  if (m_collider == nullptr)
  {
    switch (_type)
    {
    case EColliderType::Circle:
      m_collider = new CCircleCollider(_position, _size.GetX());
      break;
    case EColliderType::Rect:
      m_collider = new CRectCollider(_position, _size);
      break;
    case EColliderType::Pixel:
      m_collider = new CPixelsCollider(_position, _size, nullptr);
      break;
    }
    switch (_status)
    {
    case EColliderStatus::Static:
      CPhysicsEngine::GetInstance().AddStaticRigidBody(this);
      break;
    case EColliderStatus::Dynamic:
      CPhysicsEngine::GetInstance().AddDynamicRigidBody(this);
      break;
    }
#if COLLISION_DEBUG
    CRenderEngine::GetInstance().BindDrawCallback<CCollider, &CCollider::Render>(m_collider);
    m_collider->SetColor(0.5f, 0.1f, 0.1f, 0.3f);
#endif
  } else print_warning("Collider already exists.");
}

void CRigidBodyComponent::DestroyCollider()
{
  if (m_collider != nullptr)
  {
    CPhysicsEngine::GetInstance().EraseRigidBody(this);
    delete m_collider;
  }
}

CCollider* CRigidBodyComponent::GetCollider() const { return m_collider; }

bool CRigidBodyComponent::CheckCollision(const CCollider& _collider) const
{
  ensure(m_collider != nullptr);
  return m_collider->Collides(_collider);
}

bool CRigidBodyComponent::CheckAvailablePosition(const Vec2& _position)
{
  Vec2 backupPosition = m_collider->GetPosition();
  m_collider->SetPosition(_position);
  bool bCollision = CPhysicsEngine::GetInstance().CheckStaticCollision(m_collider);
  m_collider->SetPosition(backupPosition);
  return bCollision;
}

void CRigidBodyComponent::AddVelocityImpulse(const Vec2& _impulse)
{
  m_velocityImpulse += _impulse;
}

bool CRigidBodyComponent::OnFloor()
{
  Vec2 positionBellow(GetCollider()->GetPosition());
  positionBellow.SetY(positionBellow.GetY() + 1.f);
  return CheckAvailablePosition(positionBellow);
}
