#include "AudioBuffer.h"

#include <cstdio>
#include <cstring>



#include "AudioManager.h"
#include "MacroUtility.h"
#include "AL/al.h"


CAudioBuffer::CAudioBuffer()
  : m_alBuffer(0) {}

CAudioBuffer* CAudioBuffer::Load(const char* _filename)
{
  ensure(_filename);

  CAudioBuffer* audioBuffer = new CAudioBuffer();
  audioBuffer->m_alBuffer = CAudioManager::Get().FindALBuffer(_filename);
  return audioBuffer;
}

uint32_t CAudioBuffer::GetALBuffer() const
{
  return m_alBuffer;
}
