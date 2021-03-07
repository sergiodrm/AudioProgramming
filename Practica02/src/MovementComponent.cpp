#include "MovementComponent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "InputCodes.h"
#include "RenderEngine.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "Collider.h"

CMovementComponent::CMovementComponent()
  : m_movementInput(0.f, 0.f), m_speed(150.f), m_bProcessingInput(true)
{}

void CMovementComponent::OnCreate()
{
  Super::OnCreate();
  CInputManager::GetInstance().BindKeyboardCallback<CMovementComponent, &CMovementComponent::ProcessInput>(this);
}

void CMovementComponent::Update(float _deltaTime)
{
  if (IsActive())
  {
    CTransformComponent* transformComponent = GetOwner()->GetComponent<CTransformComponent>();
    CRigidBodyComponent* rigidBodyComponent = GetOwner()->GetComponent<CRigidBodyComponent>();
    Vec2 updatedPosition = transformComponent->GetPosition() + m_movementInput * _deltaTime;
    if (rigidBodyComponent && rigidBodyComponent->IsPhysicsActived())
    {
      if (!rigidBodyComponent->CheckAvailablePosition(updatedPosition))
      {
        transformComponent->SetPosition(updatedPosition);
        rigidBodyComponent->GetCollider()->SetPosition(updatedPosition);
      }
    }
    else
    {
      transformComponent->SetPosition(updatedPosition);
    }
  }
}

void CMovementComponent::Jump()
{
  CRigidBodyComponent* rigidBodyComponent = GetOwner()->GetComponent<CRigidBodyComponent>();
  if (rigidBodyComponent != nullptr && rigidBodyComponent->OnFloor())
  {
    rigidBodyComponent->AddVelocityImpulse(Vec2(0.f, -200.f));
  }
}

void CMovementComponent::SetControlledByPlayer(bool _process)
{
  m_bProcessingInput = _process;
}

void CMovementComponent::ProcessInput(SInputCode::EKey _key, SInputCode::EAction _action)
{
  if (IsActive() && m_bProcessingInput)
  {
    if (_key == SInputCode::EKey::A || _key == SInputCode::EKey::Left)
    {
      m_movementInput.SetX(_action == SInputCode::EAction::Press || _action == SInputCode::EAction::Maintain ? -m_speed : 0.f);
    }
    else if (_key == SInputCode::D || _key == SInputCode::EKey::Right)
    {
      m_movementInput.SetX(_action == SInputCode::EAction::Press || _action == SInputCode::EAction::Maintain ? m_speed : 0.f);
    }
    else if ((_key == SInputCode::Space || _key == SInputCode::Up || _key == SInputCode::W) && _action == SInputCode::EAction::Press)
    {
      Jump();
    }
    else if (_key == SInputCode::Escape)
    {
      CRenderEngine::GetInstance().CloseWindow();
    }
  }
}

const Vec2& CMovementComponent::GetMovementDirection() const
{
  return m_movementInput;
}

float CMovementComponent::GetSpeed() const
{
  return m_speed;
}
