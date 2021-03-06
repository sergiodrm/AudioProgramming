#pragma once

#include "SingletonBase.h"

class CAudioListener : public ISingletonBase<CAudioListener>
{
  DECLARE_SINGLETON_CLASS(CAudioListener);

public:

  static void Init();
  static CAudioListener& Get();
  static void Shutdown();

public:

  void SetListenerPosition(float _x, float _y, float _z);
  void SetListenerVelocity(float _x, float _y, float _z);
  void SetListenerOrientation(float _x, float _y, float _z);

private:

  void Init_Internal();
  void Shutdown_Internal();

private:


};

