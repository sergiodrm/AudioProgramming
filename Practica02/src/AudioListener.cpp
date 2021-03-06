#include "AudioListener.h"

#include "AL/al.h"

void CAudioListener::Init()
{
  CreateSingleton();
  GetSingletonInstance().Init_Internal();
}

CAudioListener& CAudioListener::Get()
{
  return GetSingletonInstance();
}

void CAudioListener::Shutdown()
{
  GetSingletonInstance().Shutdown_Internal();
  DestroySingleton();
}

void CAudioListener::SetListenerPosition(float _x, float _y, float _z)    { alListener3f(AL_POSITION, _x, _y, _z); }
void CAudioListener::SetListenerVelocity(float _x, float _y, float _z)    { alListener3f(AL_VELOCITY, _x, _y, _z); }
void CAudioListener::SetListenerOrientation(float _x, float _y, float _z) { alListener3f(AL_ORIENTATION, _x, _y, _z); }

void CAudioListener::Init_Internal()
{
  alListener3f(AL_POSITION, 0.f, 0.f, 0.f);
  alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);
  alListener3f(AL_ORIENTATION, 0.f, 0.f, 0.f);
}

void CAudioListener::Shutdown_Internal()
{}
