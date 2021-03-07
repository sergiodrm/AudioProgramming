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
#include "BasicShapeComponent.h"


/**
 *  Files
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
  CAudioManager::Get().CreateALBufferFromFile(AUDIO_GAME_OVER);
  CAudioBuffer* audioBuffer = CAudioBuffer::Load(AUDIO_GAME_OVER);
  ensure(audioBuffer);
  m_audioSource = new CAudioSource(audioBuffer);
  ensure(m_audioSource);

  m_sourceData.m_pitch = 1.f;
  m_sourceData.m_gain = 1.f;
  m_sourceData.m_position[0] = 0.f;
  m_sourceData.m_position[1] = 0.f;
  m_sourceData.m_position[2] = 0.f;
  m_sourceData.m_velocity[0] = 0.f;
  m_sourceData.m_velocity[1] = 0.f;
  m_sourceData.m_velocity[2] = 0.f;
  m_sourceData.m_loop = false;
  SSourceData::SetAudioSourceSettings(*m_audioSource, m_sourceData);

  m_audioSource->Play();

  // Init player game object
  CGameObject* playerGameObject = CGameObject::Create();
  CMovementComponent* movementComponent = playerGameObject->AddComponent<CMovementComponent>();
  movementComponent->SetControlledByPlayer(true);
  CAudioListenerComponent* audioListenerComponent = playerGameObject->AddComponent<CAudioListenerComponent>();
  audioListenerComponent->ActiveListener();
  CBasicShapeComponent* shapeComponent = playerGameObject->AddComponent<CBasicShapeComponent>();
  shapeComponent->SetShapeType(CBasicShapeComponent::Circle);

  playerGameObject->Active();
  


  // Bind method to receive input from player
  CInputManager::GetInstance().BindKeyboardCallback<CScene, &CScene::ReceiveInputPlayer>(this);
  delete audioBuffer;
}


void CScene::Shutdown()
{
  CAudioListener::Shutdown();
  delete m_audioSource;
  CAudioManager::Get().ClearLoadedFiles();
}

void CScene::ReceiveInputPlayer(SInputCode::EKey _key, SInputCode::EAction _action)
{
  
}
