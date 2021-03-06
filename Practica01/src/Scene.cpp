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


/**
 *  Files
 */
#define AUDIO_FILE "data/file1.wav"
#define AUDIO_MUSIC "data/music.wav"

/**
 *  Increment data
 */
#define DELTA_PITCH 0.1f
#define DELTA_GAIN 0.1f
#define DELTA_POSITION 0.1f

CScene::CScene() {}

void CScene::Init()
{
  m_audioBuffer = CAudioBuffer::Load(AUDIO_MUSIC);
  ensure(m_audioBuffer);
  m_audioSource = new CAudioSource(m_audioBuffer);
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

  CAudioListener::Init();

  // Bind method to receive input from player
  CInputManager::GetInstance().BindKeyboardCallback<CScene, &CScene::ReceiveInputPlayer>(this);
}


void CScene::Shutdown()
{
  delete m_audioSource;
  CAudioBuffer::Destroy(m_audioBuffer);
}

void CScene::ReceiveInputPlayer(SInputCode::EKey _key, SInputCode::EAction _action)
{
  switch (_key)
  {
  case SInputCode::Up:
    m_sourceData.m_pitch += DELTA_PITCH;
    break;
  case SInputCode::Down:
    m_sourceData.m_pitch -= DELTA_PITCH;
    break;
  case SInputCode::Left:
    m_sourceData.m_position[1] += DELTA_POSITION;
    break;
  case SInputCode::Right:
    m_sourceData.m_position[1] -= DELTA_POSITION;
    break;
  }
  SSourceData::SetAudioSourceSettings(*m_audioSource, m_sourceData);
}
