#pragma once
#include <cstdint>


class CAudioBuffer
{

private:

  CAudioBuffer();

public:
  
  static CAudioBuffer* Load(const char* _filename);

  uint32_t GetALBuffer() const;

///  Properties

private:

  uint32_t m_alBuffer;

};

