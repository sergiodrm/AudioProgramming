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
#include "AudioManager.h"


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

  CAudioListener::Init();
  m_audioSource->Play();

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
  if (_action == SInputCode::Press)
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
    case SInputCode::Escape:
      CRenderEngine::GetInstance().CloseWindow();
    }
    SSourceData::SetAudioSourceSettings(*m_audioSource, m_sourceData);
    print_log("---");
    print_log("Current source pitch:    %.3f", m_sourceData.m_pitch);
    print_log("Current source position: [%.3f, %.3f, %.3f]", m_sourceData.m_position[0], m_sourceData.m_position[1], m_sourceData.m_position[2]);
  }
}
