#include "TimeManager.h"
#include "glfw3.h"

CTimeManager& CTimeManager::GetTimer()
{
  return GetSingletonInstance();
}

void CTimeManager::Init(double _fixedTick)
{
  CreateSingleton();
  GetSingletonInstance().Init_Internal(_fixedTick);
}


void CTimeManager::InitToProcess()
{
  double currentTime = glfwGetTime();
  m_elapsedTime += currentTime - m_previousTime;
  m_timeBetweenFrames = currentTime - m_previousTime;
  m_previousTime = currentTime;
  if (m_elapsedTime > m_maxElapsedTime)
    m_elapsedTime = m_maxElapsedTime;
  m_totalTime += m_timeBetweenFrames;
}

bool CTimeManager::Process()
{
  if (m_elapsedTime > m_fixedTick)
  {
    m_elapsedTime -= m_fixedTick;
    return true;
  }
  return false;
}

void CTimeManager::Shutdown()
{
  DestroySingleton();
}

double CTimeManager::GetFixedTick() const
{
  return m_fixedTick;
}

double CTimeManager::GetTimeBetweenFrames() const
{
  return m_timeBetweenFrames;
}

double CTimeManager::GetTotalSeconds() const
{
  return m_totalTime;
}

void CTimeManager::Init_Internal(double _fixedTick)
{
  m_fixedTick = _fixedTick;
  m_maxElapsedTime = 0.1;
  m_elapsedTime = 0.0;
  m_previousTime = glfwGetTime();
  m_totalTime = 0.0;
}
