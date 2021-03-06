#pragma once

#include "SingletonBase.h"

// Forward declaration
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

private:

  ALCdevice* m_device;
  ALCcontext* m_context;

};

