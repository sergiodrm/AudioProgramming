#pragma once

#include "SingletonBase.h"

class CTimeManager : public ISingletonBase<CTimeManager>
{
  DECLARE_SINGLETON_CLASS(CTimeManager)
private:

  double m_elapsedTime;
  double m_maxElapsedTime;
  double m_timeBetweenFrames;
  double m_fixedTick;
  double m_previousTime;
  double m_totalTime;
  double m_logicTime;

public:

  static CTimeManager& GetTimer();

  static void Init(double _fixedTick = 0.016);
  void InitToProcess();
  bool Process();
  static void Shutdown();

  double GetFixedTick() const;
  double GetTimeBetweenFrames() const;

private:

  void Init_Internal(double _fixedTick);

};

