#pragma once

#include "Component.h"

class CCameraComponent : public CComponent
{
public:

  CCameraComponent();

  virtual void Update(float _deltaTime) override;

  void ActiveCamera();
  void DeactiveCamera();
  bool IsCameraActive() const;

private:
  bool m_bCameraActive;
};

/**
 *    Camera component - inlines definition
 */

inline void CCameraComponent::ActiveCamera()          { m_bCameraActive = true; }
inline void CCameraComponent::DeactiveCamera()        {m_bCameraActive = false; }
inline bool CCameraComponent::IsCameraActive() const  { return m_bCameraActive; }


