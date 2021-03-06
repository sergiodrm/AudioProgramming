#include "AudioSource.h"

#include "AL/al.h"

CAudioSource::CAudioSource(CAudioBuffer* _audioBuffer)
  : m_audioBuffer(_audioBuffer)
{
  alGenSources(1, &m_audioSourceBuffer);
  alSourcef(m_audioSourceBuffer, AL_PITCH, 1.f);
  alSourcef(m_audioSourceBuffer, AL_GAIN, 1.f);
  alSource3f(m_audioSourceBuffer, AL_POSITION, 0.f, 0.f, 0.f);
  alSource3f(m_audioSourceBuffer, AL_VELOCITY, 0.f, 0.f, 0.f);
}

void CAudioSource::SetPitch(float _pitch) {}

void CAudioSource::SetGain(float _gain) {}

void CAudioSource::SetLooping(bool _loop) {}

void CAudioSource::SetPosition(float _x, float _y, float _z) {}

void CAudioSource::SetVelocity(float _x, float _y, float _z) {}

void CAudioSource::Play() {}

void CAudioSource::Stop() {}

void CAudioSource::Pause() {}

bool CAudioSource::IsPlaying() const {}
