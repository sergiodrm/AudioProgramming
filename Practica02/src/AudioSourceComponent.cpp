#include "AudioSourceComponent.h"
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "TransformComponent.h"

CAudioSourceComponent::CAudioSourceComponent()
  : Super(), m_audioSource(nullptr) {}

void CAudioSourceComponent::Update(float _deltaTime)
{
  if (IsActive())
  {
    // Update position from transform component
    CTransformComponent* transformComponent = GetOwner()->GetComponent<CTransformComponent>();
    if (transformComponent)
    {
      Vec2 position = transformComponent->GetPosition();
      m_audioSource->SetPosition(position.GetX(), position.GetY(), 0.f);
      //print_log("Audio source position: [%.0f, %.0f]", position.GetX(), position.GetY());
    }

    // Update velocity from movement component
    CMovementComponent* movementComponent = GetOwner()->GetComponent<CMovementComponent>();
    if (movementComponent)
    {
      Vec2 velocity = movementComponent->GetLastFrameVelocity();
      m_audioSource->SetVelocity(velocity.GetX(), velocity.GetY(), 0.f);
      //print_log("Audio source velocity: [%.0f, %.0f]", velocity.GetX(), velocity.GetY());
    }
  }
}

void CAudioSourceComponent::OnDestroy()
{
  delete m_audioSource;
}

void CAudioSourceComponent::LoadAudio(const char* _filename)
{
  if (m_audioSource)
    return;

  CAudioBuffer* audioBuffer = CAudioBuffer::Load(_filename);
  ensure(audioBuffer);
  m_audioSource = new CAudioSource(audioBuffer);
  delete audioBuffer;
}

CAudioSource* CAudioSourceComponent::GetAudioSource() const { return m_audioSource; }
