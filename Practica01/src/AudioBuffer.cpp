#include "AudioBuffer.h"
#include "MacroUtility.h"
#include <fstream>
#include <sstream>

CAudioBuffer* CAudioBuffer::Load(const char* _filename)
{
  ensure(_filename);
  std::ifstream stream(_filename, std::ios_base::binary);
  std::stringstream sstream;
  sstream << stream.rdbuf();
  
  return nullptr;
}
