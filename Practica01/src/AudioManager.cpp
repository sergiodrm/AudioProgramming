#include "AudioManager.h"

#include "MacroUtility.h"
#include "AL/alc.h"

void CAudioManager::Init()
{
  CreateSingleton();
  GetSingletonInstance().Init_Internal();
}

CAudioManager& CAudioManager::Get()
{
  return GetSingletonInstance();
}

void CAudioManager::Shutdown()
{
  GetSingletonInstance().Shutdown_Internal();
  DestroySingleton();
}

void CAudioManager::Init_Internal()
{
  // Init openAL
  PRINT_LOG("Creating new OpenAL device...");
  m_device = alcOpenDevice(nullptr);
  ensure_msg(m_device, "Audio manager init failed");
  m_context = alcCreateContext(m_device, nullptr);
  ensure_msg(m_context, "Audio manager init failed");
  PRINT_LOG("Setting OpenAL context...");
  alcMakeContextCurrent(m_context);

  PRINT_LOG("OpenAL initialized successfully.");
}
void CAudioManager::Shutdown_Internal()
{
  // Destroy context and device
  alcMakeContextCurrent(nullptr);
  alcDestroyContext(m_context);
  alcCloseDevice(m_device);
  PRINT_LOG("OpenAL terminated successfully.");
}
