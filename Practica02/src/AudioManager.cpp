#include "AudioManager.h"


#include "AudioListener.h"
#include "MacroUtility.h"
#include "AL/al.h"
#include "AL/alc.h"

void CAudioManager::Init()
{
  CreateSingleton();
  GetSingletonInstance().Init_Internal();
}

CAudioManager& CAudioManager::Get()
{
  return GetSingletonInstance();
}

void CAudioManager::Shutdown()
{
  GetSingletonInstance().Shutdown_Internal();
  DestroySingleton();
}

void CAudioManager::Init_Internal()
{
  // Init openAL
  print_log("Creating new OpenAL device...");
  m_device = alcOpenDevice(nullptr);
  ensure_msg(m_device, "Audio manager init failed");
  m_context = alcCreateContext(m_device, nullptr);
  ensure_msg(m_context, "Audio manager init failed");
  print_log("Setting OpenAL context...");
  alcMakeContextCurrent(m_context);
  CAudioListener::Init();

  print_log("OpenAL initialized successfully.");
}

void CAudioManager::Shutdown_Internal()
{
  ClearLoadedFiles();

  // Destroy context and device
  alcMakeContextCurrent(nullptr);
  alcDestroyContext(m_context);
  alcCloseDevice(m_device);
  print_log("OpenAL terminated successfully.");
}

unsigned CAudioManager::CreateALBufferFromFile(const char* _filename)
{
  ensure(_filename);

  // Check if buffer already exists
  ALuint buffer = FindALBuffer(_filename);
  if (buffer != AL_INVALID_BUFFER)
  {
    print_log("%s file loaded previously.");
    return buffer;
  }
  print_log("Creating new audio buffer for %s file.", _filename);

  // Load wav file
  SWavData* wavData = LoadWavFile(_filename);
  if (!wavData)
  {
    print_error("Failed to read wav %s file", _filename);
    return AL_INVALID_BUFFER;
  }

  // Generate and fill ALBuffer
  al_call(alGenBuffers(1, &buffer));
  if (wavData->header.bitsPerSample == 8)
  {
    al_call(
      alBufferData(buffer, wavData->header.numChannels == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8, wavData->data,
        wavData->dataSize, wavData->header.sampleRate));
  }
  else if (wavData->header.bitsPerSample == 16)
  {
    al_call(
      alBufferData(buffer, wavData->header.numChannels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, wavData->data,
        wavData->dataSize, wavData->header.sampleRate));
  }
  m_audioFilesLoaded.insert(std::make_pair(_filename, buffer));
  delete wavData->data;
  delete wavData;
  return buffer;
}

unsigned CAudioManager::FindALBuffer(const char* _filename) const
{
  std::map<const char*, unsigned>::const_iterator iterator = m_audioFilesLoaded.find(_filename);
  if (iterator != m_audioFilesLoaded.end())
  {
    return iterator->second;
  }
  return AL_INVALID_BUFFER;
}

void CAudioManager::RemoveLoadedFile(const char* _filename)
{
  ensure(_filename);
  unsigned buffer = FindALBuffer(_filename);
  if (buffer != AL_INVALID_BUFFER)
  {
    al_call(alDeleteBuffers(1, &buffer));
  }
}

void CAudioManager::ClearLoadedFiles()
{
  for (std::pair<const char* const, unsigned>& iterator : m_audioFilesLoaded)
  {
    if (iterator.second != AL_INVALID_BUFFER)
    {
      print_log("Removing %s from memory.", iterator.first);
      unsigned* buffer = &iterator.second;
      al_call(alDeleteBuffers(1, buffer));
    }
  }
}

void CAudioManager::SetDopplerFactor(float _factor)
{
  al_call(alDopplerFactor(_factor));
}

void CAudioManager::SetDopplerVelocity(float _speed)
{
  al_call(alDopplerVelocity(_speed));
}

CAudioManager::SWavData* CAudioManager::LoadWavFile(const char* _filename)
{
  ensure(_filename);
  SWavData* wavData = new SWavData();

  /// Read file ---

  // Open file
  FILE* fid = fopen(_filename, "rb");
  if (!fid)
  {
    print_warning("File not found or invalid file");
    return nullptr;
  }
  print_log("Reading %s file...", _filename);

  // Read header wav file
  size_t bytesRead = fread(&wavData->header, 1, sizeof(SWavHeader), fid);
  print_log("Header wav %s: %d bytes", _filename, bytesRead);
  if (bytesRead != sizeof(SWavHeader))
  {
    print_warning("Wav header was not successfully read.");
    return nullptr;
  }

  // Check FmtChunkSize
  if (wavData->header.fmtChunkSize > AL_CHUNK_SIZE_FLAG)
  {
    // If FmtChunkSize is greater than 16, then there are more header data. It must be ignored.
    uint16_t extraParamsSize;
    bytesRead = fread(&extraParamsSize, 1, sizeof(extraParamsSize), fid);
    ensure(bytesRead > 0);

    // Now read the amount of bytes of specified on extraParamsSize.
    // @todo check change from jump with fread to jump with fseek
    fseek(fid, extraParamsSize, SEEK_CUR);
  }

  // Find "data" string in file from here
  char dataString[5];
  dataString[4] = '\0';
  wavData->data = nullptr;
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

    // Check if it is the correct field
    if (strcmp(dataString, "data") != 0)
    {
      // If not, jump to next chunk
      fseek(fid, bytesToRead, SEEK_CUR);
    }
    else
    {
      bDataStringFoundFlag = true;
      // Alloc memory and read
      wavData->data = new char[bytesToRead];
      wavData->dataSize = fread(wavData->data, 1, bytesToRead, fid);
      ensure(wavData->dataSize > 0);
      ensure(wavData->data);
    }

    // Check end of file
    if (!bDataStringFoundFlag && feof(fid))
    {
      print_error("Data not found in %s file", _filename);
      return nullptr;
    }
  }
  while (!bDataStringFoundFlag);

  print_log("%s file contains %d bytes of data.", _filename, bytesRead);
  return wavData;
}
