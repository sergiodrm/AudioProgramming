#pragma once
#include <cstdint>


class CAudioBuffer;

class CAudioSource
{

public:

  CAudioSource(CAudioBuffer* _audioBuffer);
  ~CAudioSource();

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

  uint32_t m_audioSourceBuffer;
};

/// ----

struct SSourceData
{
  float m_pitch;
  float m_gain;
  bool m_loop;
  float m_position[3];
  float m_velocity[3];
  static void SetAudioSourceSettings(CAudioSource& _source, const SSourceData& _data);
};

