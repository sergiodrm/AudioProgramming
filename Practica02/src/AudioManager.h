#pragma once

#include <map>

#include "SingletonBase.h"

// Forward declaration
class CAudioBuffer;
struct ALCdevice_struct;
typedef ALCdevice_struct ALCdevice;
struct ALCcontext_struct;
typedef ALCcontext_struct ALCcontext;

class CAudioManager : public ISingletonBase<CAudioManager>
{
  DECLARE_SINGLETON_CLASS(CAudioManager);

public:

  static void Init();
  static CAudioManager& Get();
  static void Shutdown();

private:

  void Init_Internal();
  void Shutdown_Internal();

public:

  unsigned CreateALBufferFromFile(const char* _filename);
  unsigned FindALBuffer(const char* _filename) const;
  void RemoveLoadedFile(const char* _filename);
  void ClearLoadedFiles();

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

  struct SWavData
  {
    SWavHeader header;
    char* data;
    size_t dataSize;
  };

  static SWavData* LoadWavFile(const char* _filename);

private:
  
  /// OpenAL properties
  
  ALCdevice* m_device;
  ALCcontext* m_context;
  
  /**
   * @todo audio files handling should be here
   */
  std::map<const char*, unsigned> m_audioFilesLoaded;
};

