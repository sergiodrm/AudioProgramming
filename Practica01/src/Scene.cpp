#include "Scene.h"


#include "BackgroundComponent.h"
#include "CameraComponent.h"
#include "Collider.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "RenderEngine.h"
#include "AudioSourceComponent.h"
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "AudioListenerComponent.h"
#include "AudioManager.h"
#include "BasicShapeComponent.h"
#include "TransformComponent.h"


/**
 *  Files: to change the music, please change the macro in creation (line 42) and when it is loaded (line 48)
 */
#define AUDIO_FILE "data/file1.wav"
#define AUDIO_MUSIC "data/music.wav"
#define AUDIO_TAKE_ON_ME "data/takeonme.wav"
#define AUDIO_GAME_OVER "data/gameover.wav"

/**
 *  Increment data
 */
#define DELTA_PITCH 0.02f
#define DELTA_GAIN 0.1f
#define DELTA_POSITION 0.5f

CScene::CScene() {}

void CScene::Init()
{
  // Load audio file
  CAudioManager::Get().CreateALBufferFromFile(AUDIO_MUSIC); // !!

  // Create source game object
  {
    m_sourceGameObject = CGameObject::Create();
    CAudioSourceComponent* audioSourceComponent = m_sourceGameObject->AddComponent<CAudioSourceComponent>();
    audioSourceComponent->LoadAudio(AUDIO_MUSIC); // !!
    CMovementComponent* movementComponent = m_sourceGameObject->AddComponent<CMovementComponent>();
    movementComponent->SetControlledByPlayer(true);
    CBasicShapeComponent* renderComponent = m_sourceGameObject->AddComponent<CBasicShapeComponent>();
    renderComponent->SetColor(0.5f, 0.3f, 0.01f, 0.7f);
    renderComponent->SetSize(Vec2(25.f, 25.f));
    m_sourceGameObject->Active();
    m_sourceGameObject->GetComponent<CTransformComponent>()->SetPosition(
      CRenderEngine::GetInstance().GetWindowSize() * 0.5f);
  }

  // Create listener game object
  {
    CGameObject* listenerGameObject = CGameObject::Create();
    CAudioListenerComponent* audioListenerComponent = listenerGameObject->AddComponent<CAudioListenerComponent>();
    audioListenerComponent->ActiveListener();
    CBasicShapeComponent* renderComponent = listenerGameObject->AddComponent<CBasicShapeComponent>();
    renderComponent->SetColor(0.8f, 0.8f, 0.8f, 0.7f);
    renderComponent->SetSize(Vec2(10.f, 10.f));
    listenerGameObject->Active();
    listenerGameObject->GetComponent<CTransformComponent>()->SetPosition(
      CRenderEngine::GetInstance().GetWindowSize() * 0.5f);
  }

  m_sourceData.m_pitch = 1.f;
  m_sourceData.m_gain = 1.f;
  m_sourceData.m_loop = false;
  SSourceData::SetAudioSourceSettings(*m_sourceGameObject->GetComponent<CAudioSourceComponent>()->GetAudioSource(),
                                      m_sourceData);


  m_sourceGameObject->GetComponent<CAudioSourceComponent>()->GetAudioSource()->Play();
  CAudioManager::Get().SetDopplerFactor(0.f);

  // Bind method to receive input from player
  CInputManager::GetInstance().BindKeyboardCallback<CScene, &CScene::ReceiveInputPlayer>(this);
}


void CScene::Shutdown()
{
  CAudioListener::Shutdown();
}

void CScene::ReceiveInputPlayer(SInputCode::EKey _key, SInputCode::EAction _action)
{
  if (_action == SInputCode::Press)
  {
    switch (_key)
    {
    case SInputCode::Up: m_sourceData.m_pitch += DELTA_PITCH;
      break;
    case SInputCode::Down: m_sourceData.m_pitch -= DELTA_PITCH;
      break;
    case SInputCode::Escape: CRenderEngine::GetInstance().CloseWindow();
    }
    SSourceData::SetAudioSourceSettings(*m_sourceGameObject->GetComponent<CAudioSourceComponent>()->GetAudioSource(),
                                        m_sourceData);
    print_log("---");
    print_log("Current source pitch:    %.3f", m_sourceData.m_pitch);
  }
}
