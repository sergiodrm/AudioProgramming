#pragma once

#include "SpriteComponent.h"

class CBackgroundComponent : public CSpriteComponent
{
public:

  CBackgroundComponent();
  virtual void Update(float _deltaTime) override;
  virtual void Render() const override;

  float GetScrollRatio() const;
  const Vec2& GetScrollSpeed() const;
  void SetScrollRatio(float _scrollRatio);
  void SetScrollSpeed(const Vec2& _scrollSpeed);

private:

  float m_scrollRatio;
  Vec2 m_scrollSpeed;
  Vec2 m_uv[2];

};


inline float CBackgroundComponent::GetScrollRatio() const                   { return m_scrollRatio; }
inline const Vec2& CBackgroundComponent::GetScrollSpeed() const             { return m_scrollSpeed; }
inline void CBackgroundComponent::SetScrollRatio(float _scrollRatio)        { m_scrollRatio = _scrollRatio; }
inline void CBackgroundComponent::SetScrollSpeed(const Vec2& _scrollSpeed)  { m_scrollSpeed = _scrollSpeed; }

