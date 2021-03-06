#include "AudioSource.h"


#include "AudioBuffer.h"
#include "AL/al.h"

CAudioSource::CAudioSource(CAudioBuffer* _audioBuffer)
{
  alGenSources(1, &m_audioSourceBuffer);
  alSourcef(m_audioSourceBuffer, AL_PITCH, 1.f);
  alSourcef(m_audioSourceBuffer, AL_GAIN, 1.f);
  alSource3f(m_audioSourceBuffer, AL_POSITION, 0.f, 0.f, 0.f);
  alSource3f(m_audioSourceBuffer, AL_VELOCITY, 0.f, 0.f, 0.f);
  alSourcei(m_audioSourceBuffer, AL_BUFFER, _audioBuffer->GetALBuffer());
}

CAudioSource::~CAudioSource()
{
  alDeleteSources(1, &m_audioSourceBuffer);
}

void CAudioSource::SetPitch(float _pitch)                     { alSourcef(m_audioSourceBuffer, AL_PITCH, _pitch); }
void CAudioSource::SetGain(float _gain)                       { alSourcef(m_audioSourceBuffer, AL_GAIN, _gain); }
void CAudioSource::SetLooping(bool _loop)                     { alSourcei(m_audioSourceBuffer, AL_LOOPING, _loop ? 1 : 0); }
void CAudioSource::SetPosition(float _x, float _y, float _z)  { alSource3f(m_audioSourceBuffer, AL_POSITION, _x, _y, _z); }
void CAudioSource::SetVelocity(float _x, float _y, float _z)  { alSource3f(m_audioSourceBuffer, AL_VELOCITY, _x, _y, _z); }

void CAudioSource::Play()   { alSourcePlay(m_audioSourceBuffer); }
void CAudioSource::Stop()   { alSourceStop(m_audioSourceBuffer); }
void CAudioSource::Pause()  { alSourcePause(m_audioSourceBuffer); }

bool CAudioSource::IsPlaying() const
{
  ALint playing;
  alGetSourcei(m_audioSourceBuffer, AL_PLAYING, &playing);
  return playing == AL_TRUE;
}
