#pragma once
#include <cstdint>


class CAudioBuffer;

class CAudioSource
{

public:

  CAudioSource(CAudioBuffer* _audioBuffer);

public:

  void SetPitch(float _pitch);
  void SetGain(float _gain);
  void SetLooping(bool _loop);
  void SetPosition(float _x, float _y, float _z);
  void SetVelocity(float _x, float _y, float _z);

  void Play();
  void Stop();
  void Pause();
  bool IsPlaying() const;

private:

  CAudioBuffer* m_audioBuffer;
  uint32_t m_audioSourceBuffer;
};

