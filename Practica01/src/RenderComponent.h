#pragma once

#include "Component.h"

class CRenderComponent : public CComponent
{
public:

  CRenderComponent() {}

  virtual void Render() const = 0;
};

