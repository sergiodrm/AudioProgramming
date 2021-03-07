#include "BasicShapeComponent.h"

#include "GameObject.h"
#include "litegfx.h"
#include "TransformComponent.h"

CBasicShapeComponent::CBasicShapeComponent()
  : m_shapeType(EShapes::Circle), m_size(100.f, 100.f), m_color{1.f, 1.f, 1.f, 1.f}
{}

void CBasicShapeComponent::Update(float _deltaTime) {}

void CBasicShapeComponent::Render() const
{
  if (IsActive())
  {
    Vec2 position = GetOwner()->GetComponent<CTransformComponent>()->GetPosition();
    lgfx_setblend(BLEND_ALPHA);
    lgfx_setcolor(m_color[0], m_color[1], m_color[2], m_color[3]);
    switch (m_shapeType)
    {
    case EShapes::Rectangle:
      lgfx_drawrect(position.GetX(), position.GetY(), m_size.GetX(), m_size.GetY());
      break;
    case EShapes::Circle:
      lgfx_drawoval(position.GetX() - 0.5f * m_size.GetX(), position.GetY() - 0.5f * m_size.GetY(), m_size.GetX(), m_size.GetY());
      break;
    }
  }
}

void CBasicShapeComponent::SetShapeType(EShapes _type)
{
  m_shapeType = _type;
}

void CBasicShapeComponent::SetColor(float _r, float _g, float _b, float _a)
{
  m_color[0] = _r;
  m_color[1] = _g;
  m_color[2] = _b;
  m_color[3] = _a;
}

void CBasicShapeComponent::SetSize(const Vec2& _size)
{
  m_size = _size;
}
