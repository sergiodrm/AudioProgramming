#pragma once

#include "litegfx.h"
#include "RenderComponent.h"
#include "Vec2.h"

class CSpriteComponent : public CRenderComponent
{
public:

  CSpriteComponent();

  virtual void Update(float _deltaTime) override;
  virtual void Render() const override;

  void LoadTexture(const char* _filename, int _horizontalFrames, int _verticalFrames);
  const ltex_t* GetTexture() const;
  void SetTexture(const ltex_t* _textureId, int _horizontalFrames, int _verticalFrames);

  lblend_t GetBlend() const;
  void SetBlend(lblend_t _blendMode);

  float GetRed() const;
  float GetGreen() const;
  float GetBlue() const;
  float GetAlpha() const;
  void SetColor(float _r, float _g, float _b, float _a);

  float GetAngle() const;
  void SetAngle(float _angle);

  float GetScale() const;
  void SetScale(float _scale);

  Vec2 GetSize() const;

  const Vec2& GetPivot() const;
  void SetPivot(const Vec2& _pivot);

  float GetHorizontalFrames() const;
  float GetVerticalFrames() const;

  int GetFPS() const;
  void SetFPS(int _iFps);

  float GetCurrentFrame() const;
  void SetCurrentFrame(int _frame);

  void SetReflexSprite(bool _reflexX, bool _reflexY);

protected:

  const ltex_t* m_textureId;
  float m_color[4];
  lblend_t m_blendMode;
  float m_rotation;
  float m_scale;
  float m_fps;

  Vec2 m_pivot;
  int m_horizontalFrames;
  int m_verticalFrames;
  float m_currentFrame;

  bool m_reflexSpriteX;
  bool m_reflexSpriteY;
};

