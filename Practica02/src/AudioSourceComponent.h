#pragma once

#include "Component.h"

class CAudioSource;

class CAudioSourceComponent : public CComponent
{
public:

  CAudioSourceComponent();

public:

  virtual void Update(float _deltaTime) override;
  virtual void OnDestroy() override;

public:

  void LoadAudio(const char* _filename);
  CAudioSource* GetAudioSource() const;

private:

  CAudioSource* m_audioSource;

};

