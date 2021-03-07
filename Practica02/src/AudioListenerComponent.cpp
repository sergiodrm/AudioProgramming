
#include "AudioListenerComponent.h"
#include "AudioListener.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "TransformComponent.h"

CAudioListenerComponent::CAudioListenerComponent()
  : Super(), m_listenerActive() {}

void CAudioListenerComponent::Update(float _deltaTime)
{
  if (IsActive() && IsListenerActive())
  {

    // Update position from transform component
    CTransformComponent* transformComponent = GetOwner()->GetComponent<CTransformComponent>();
    if (transformComponent)
    {
      Vec2 position = transformComponent->GetPosition();
      CAudioListener::Get().SetListenerPosition(position.GetX(), position.GetY(), 0.f);
    }

    // Update velocity from movement component
    CMovementComponent* movementComponent = GetOwner()->GetComponent<CMovementComponent>();
    if (movementComponent)
    {
      Vec2 velocity = movementComponent->GetMovementDirection() * movementComponent->GetSpeed();
      CAudioListener::Get().SetListenerVelocity(velocity.GetX(), velocity.GetY(), 0.f);
    }
  }
}

void CAudioListenerComponent::ActiveListener() { m_listenerActive = true; }
void CAudioListenerComponent::DeactiveListener() { m_listenerActive = false; }
