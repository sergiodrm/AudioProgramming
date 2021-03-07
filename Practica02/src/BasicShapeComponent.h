#pragma once

#include "RenderComponent.h"
#include "Vec2.h"

class CBasicShapeComponent : public CRenderComponent
{
public:

  enum EShapes : int
  {
    Rectangle, Circle
  };

public:

  CBasicShapeComponent();

  virtual void Update(float _deltaTime) override;
  virtual void Render() const override;

  void SetShapeType(EShapes _type);
  void SetColor(float _r, float _g, float _b, float _a);
  void SetSize(const Vec2& _size);

private:

  EShapes m_shapeType;
  Vec2 m_size;
  float m_color[4];

};

