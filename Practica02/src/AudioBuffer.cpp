#include "AudioBuffer.h"

#include <cstdio>
#include <cstring>


#include "MacroUtility.h"
#include "AL/al.h"

#define CHUNK_SIZE_FLAG 16

#define al_call(_CALL) \
  { \
    alGetError(); \
    (_CALL); \
    ALenum alError = alGetError(); \
    if (alError != AL_NO_ERROR) \
    { \
      PRINT_ERROR("Error at OpenAL function %s (code: %d)", #_CALL, alError); \
      __debugbreak(); \
    } \
  } \

CAudioBuffer::CAudioBuffer()
  : m_alBuffer(0) {}

CAudioBuffer* CAudioBuffer::Load(const char* _filename)
{
  ensure(_filename);

  /// Read file ---

  // Open file
  FILE* fid = fopen(_filename, "rb");
  if (!fid)
  {
    PRINT_WARNING("File not found or invalid file");
    return nullptr;
  }
  PRINT_LOG("Reading %s file...", _filename);

  // Read header wav file
  SWavHeader header;
  size_t bytesRead = fread(&header, 1, sizeof(SWavHeader), fid);
  PRINT_LOG("Header wav %s: %d bytes", _filename, bytesRead);
  if (bytesRead != sizeof(SWavHeader))
  {
    PRINT_WARNING("Wav header was not successfully read.");
    return nullptr;
  }

  // Check FmtChunkSize
  if (header.fmtChunkSize > CHUNK_SIZE_FLAG)
  {
    // If FmtChunkSize is greater than 16, then there are more header data. It must be ignored.
    uint16_t extraParamsSize;
    bytesRead = fread(&extraParamsSize, 1, sizeof(extraParamsSize), fid);
    ensure(bytesRead > 0);

    // Now read the amount of bytes of specified on extraParamsSize.
    if (extraParamsSize > 0)
    {
      char* extraParams = new char[extraParamsSize];
      bytesRead = fread(extraParams, 1, static_cast<size_t>(extraParamsSize), fid);
      ensure(bytesRead > 0);
      delete[] extraParams;
    }
  }

  // Find "data" string in file from here
  char dataString[5];
  dataString[4] = '\0';
  char* dataField = nullptr;
  bool bDataStringFoundFlag = false;
  do
  {
    // Read next 4 bytes to compare with "data"
    bytesRead = fread(dataString, 1, sizeof(dataString) - 1, fid);
    ensure_msg(bytesRead > 0, "Data string not found in wav file");

    // Read next 4 bytes to know how many bytes this field has
    uint32_t bytesToRead;
    bytesRead = fread(&bytesToRead, 1, sizeof(bytesToRead), fid);
    ensure(bytesRead > 0);

    // Alloc memory and read
    dataField = new char[bytesToRead];
    bytesRead = fread(dataField, 1, bytesToRead, fid);
    ensure(bytesRead > 0);

    // Check if it is the correct field
    if (strcmp(dataString, "data") != 0)
    {
      // If not, delete read data
      delete[] dataField;
    } else bDataStringFoundFlag = true;

    if (!bDataStringFoundFlag && feof(fid))
    {
      PRINT_ERROR("Data not found in %s file", _filename);
      return nullptr;
    }
  } while(!bDataStringFoundFlag);

  ensure(dataField);
  PRINT_LOG("%s file contains %d bytes of data.", _filename, bytesRead);

  /// ---

  // Generate audio buffer in OpenAL
  CAudioBuffer* audioBuffer = new CAudioBuffer();
  al_call(alGenBuffers(1, &audioBuffer->m_alBuffer));

  // Fill buffer
  if (header.bitsPerSample == 8)
  {
    al_call(alBufferData(audioBuffer->m_alBuffer, header.numChannels == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8, dataField, bytesRead, header.sampleRate));
  }
  else if (header.bitsPerSample == 16)
  {
    al_call(alBufferData(audioBuffer->m_alBuffer, header.numChannels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, dataField, bytesRead, header.sampleRate));
  }

  delete[] dataField;

  PRINT_LOG("%s file loaded successfully. (AL buffer id: %d)", _filename, audioBuffer->m_alBuffer);
  return audioBuffer;
}

void CAudioBuffer::Destroy(CAudioBuffer* _buffer)
{
  if (_buffer)
  {
    al_call(alDeleteBuffers(1, &_buffer->m_alBuffer));
    delete _buffer;
  }
}

uint32_t CAudioBuffer::GetALBuffer() const
{
  return m_alBuffer;
}
