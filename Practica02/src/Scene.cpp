#include "Scene.h"


#include "BackgroundComponent.h"
#include "CameraComponent.h"
#include "Collider.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "RenderEngine.h"
#include "RigidBodyComponent.h"
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "AudioListenerComponent.h"
#include "AudioManager.h"
#include "AudioSourceComponent.h"
#include "BasicShapeComponent.h"
#include "CircleMovementComponent.h"
#include "TransformComponent.h"


/**
 *  Files
 */
#define AUDIO_ENGINE "data/engine.wav"

/**
 *  Increment data
 */
#define DELTA_PITCH 0.02f
#define DELTA_GAIN 0.1f
#define DELTA_POSITION 0.5f

/**
 *  Misc constants 
 */
#define DOPPLER_SPEED 343.3f

CScene::CScene() {}

void CScene::Init()
{
  // Load audio files in memory
  CAudioManager::Get().CreateALBufferFromFile(AUDIO_ENGINE);

  {
    // Init player game object
    CGameObject* playerGameObject = CGameObject::Create();
    CMovementComponent* movementComponent = playerGameObject->AddComponent<CMovementComponent>();
    movementComponent->SetControlledByPlayer(true);
    CAudioListenerComponent* audioListenerComponent = playerGameObject->AddComponent<CAudioListenerComponent>();
    audioListenerComponent->ActiveListener();
    CBasicShapeComponent* shapeComponent = playerGameObject->AddComponent<CBasicShapeComponent>();
    shapeComponent->SetShapeType(CBasicShapeComponent::Circle);
    playerGameObject->Active();

    Vec2 screenSize = CRenderEngine::GetInstance().GetWindowSize();
    playerGameObject->GetComponent<CTransformComponent>()->SetPosition(
      Vec2(screenSize.GetX() * 0.5f, screenSize.GetY() - 150.f));
  }

  {
    // Init audio source game object
    CGameObject* sourceGameObject = CGameObject::Create();
    CAudioSourceComponent* audioSourceComponent = sourceGameObject->AddComponent<CAudioSourceComponent>();
    audioSourceComponent->LoadAudio(AUDIO_ENGINE);
    CBasicShapeComponent* shapeComponent = sourceGameObject->AddComponent<CBasicShapeComponent>();
    shapeComponent->SetColor(0.5f, 0.1f, 0.1f, 1.f);
    shapeComponent->SetSize(Vec2(20.f, 20.f));
    audioSourceComponent->GetAudioSource()->SetLooping(true);
    CCircleMovementComponent* circleMovementComponent = sourceGameObject->AddComponent<CCircleMovementComponent>();
    circleMovementComponent->SetCenter(CRenderEngine::GetInstance().GetWindowSize() / 2.f);
    circleMovementComponent->SetRadius(CRenderEngine::GetInstance().GetWindowSize().GetY() / 4.f);
    sourceGameObject->Active();

    CAudioManager::Get().SetDopplerFactor(2.f);
    CAudioManager::Get().SetDopplerVelocity(DOPPLER_SPEED);
    audioSourceComponent->GetAudioSource()->Play();
  }

  // Bind method to receive input from player
  CInputManager::GetInstance().BindKeyboardCallback<CScene, &CScene::ReceiveInputPlayer>(this);
}


void CScene::Shutdown()
{
  CAudioListener::Shutdown();
}

void CScene::ReceiveInputPlayer(SInputCode::EKey _key, SInputCode::EAction _action)
{ }
