#pragma once
#include <cstdint>


class CAudioBuffer
{
private:

  struct SWavHeader
  {
    uint32_t chunkID; 
    uint32_t riffChunkSize;
    uint32_t format; 
    uint32_t fmtSubchunkID;
    uint32_t fmtChunkSize;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
  };

private:

  CAudioBuffer();

public:

  static CAudioBuffer* Load(const char* _filename);
  static void Destroy(CAudioBuffer* _buffer);

  uint32_t GetALBuffer() const;


///  Properties

private:

  uint32_t m_alBuffer;

};

