#include "AudioSource.h"


#include "AudioBuffer.h"
#include "AudioListenerComponent.h"
#include "AL/al.h"

CAudioSource::CAudioSource(CAudioBuffer* _audioBuffer)
{
  // Generate OpenAL audio source
  al_call(alGenSources(1, &m_audioSourceBuffer));

  // Set configuration
  al_call(alSourcef(m_audioSourceBuffer, AL_PITCH, 1.f));
  al_call(alSourcef(m_audioSourceBuffer, AL_GAIN, 1.f));
  al_call(alSource3f(m_audioSourceBuffer, AL_POSITION, 0.f, 0.f, 0.f));
  al_call(alSource3f(m_audioSourceBuffer, AL_VELOCITY, 0.f, 0.f, 0.f));

  // Volume configuration
  al_call(alSourcef(m_audioSourceBuffer, AL_MAX_DISTANCE, 100.f));
  al_call(alSourcef(m_audioSourceBuffer, AL_REFERENCE_DISTANCE, 15.f));

  // Bind input buffer
  al_call(alSourcei(m_audioSourceBuffer, AL_BUFFER, _audioBuffer->GetALBuffer()));
}

CAudioSource::~CAudioSource()
{
  alDeleteSources(1, &m_audioSourceBuffer);
}

void CAudioSource::SetPitch(float _pitch)
{
  al_call(alSourcef(m_audioSourceBuffer, AL_PITCH, _pitch));
}

void CAudioSource::SetGain(float _gain)
{
  al_call(alSourcef(m_audioSourceBuffer, AL_GAIN, _gain));
}

void CAudioSource::SetLooping(bool _loop)
{
  al_call(alSourcei(m_audioSourceBuffer, AL_LOOPING, _loop ? 1 : 0));
}

void CAudioSource::SetPosition(float _x, float _y, float _z)
{
  al_call(alSource3f(m_audioSourceBuffer, AL_POSITION, _x, _y, _z));
}

void CAudioSource::SetVelocity(float _x, float _y, float _z)
{
  al_call(alSource3f(m_audioSourceBuffer, AL_VELOCITY, _x, _y, _z));
}

void CAudioSource::Play()
{
  al_call(alSourcePlay(m_audioSourceBuffer));
}

void CAudioSource::Stop()
{
  al_call(alSourceStop(m_audioSourceBuffer));
}

void CAudioSource::Pause()
{
  al_call(alSourcePause(m_audioSourceBuffer));
}

bool CAudioSource::IsPlaying() const
{
  ALint playing;
  al_call(alGetSourcei(m_audioSourceBuffer, AL_PLAYING, &playing));
  return playing == AL_TRUE;
}


/// ----

void SSourceData::SetAudioSourceSettings(CAudioSource& _source, const SSourceData& _data)
{
  _source.SetPitch(_data.m_pitch);
  _source.SetGain(_data.m_gain);
  _source.SetLooping(_data.m_loop);
}
