#include "SpriteComponent.h"

#include "GameObject.h"
#include "MacroUtility.h"
#include "RenderEngine.h"
#include "TextureManager.h"
#include "TransformComponent.h"

#define NUMBER_CHANNELS_RGBA 4

void CSpriteComponent::LoadTexture(const char* _filename, int _horizontalFrames, int _verticalFrames)
{
  m_textureId = CTextureManager::GetInstance().CreateTexture(_filename);
  ensure(m_textureId != nullptr);
}

CSpriteComponent::CSpriteComponent()
  : m_textureId(nullptr), m_blendMode(BLEND_ALPHA),
  m_horizontalFrames(1), m_verticalFrames(1),
  m_pivot(0.f, 0.f),
  m_rotation(0.f), m_scale(1.f), m_fps(8.f),
  m_color{ 1.f, 1.f, 1.f, 1.f }
{}

const ltex_t* CSpriteComponent::GetTexture() const
{
  return m_textureId;
}

void CSpriteComponent::SetTexture(const ltex_t* _textureId, int _horizontalFrames, int _verticalFrames)
{
  if (_textureId != nullptr) m_textureId = _textureId;
  m_horizontalFrames = _horizontalFrames;
  m_verticalFrames = _verticalFrames;
}

lblend_t CSpriteComponent::GetBlend() const
{
  return m_blendMode;
}

void CSpriteComponent::SetBlend(lblend_t _blendMode)
{
  m_blendMode = _blendMode;
}

float CSpriteComponent::GetRed() const
{
  return m_color[0];
}

float CSpriteComponent::GetGreen() const
{
  return m_color[1];
}

float CSpriteComponent::GetBlue() const
{
  return m_color[2];
}

float CSpriteComponent::GetAlpha() const
{
  return m_color[3];
}

void CSpriteComponent::SetColor(float _r, float _g, float _b, float _a)
{
  m_color[0] = Math::Clamp<float>(_r, 0.f, 1.f);
  m_color[1] = Math::Clamp<float>(_g, 0.f, 1.f);
  m_color[2] = Math::Clamp<float>(_b, 0.f, 1.f);
  m_color[3] = Math::Clamp<float>(_a, 0.f, 1.f);
}

float CSpriteComponent::GetAngle() const
{
  return m_rotation;
}

void CSpriteComponent::SetAngle(float _angle)
{
  m_rotation = _angle;
}

float CSpriteComponent::GetScale() const
{
  return m_scale;
}

void CSpriteComponent::SetScale(float _scale)
{
  m_scale = Math::Clamp<float>(_scale, 0.f, 1.f);
}

Vec2 CSpriteComponent::GetSize() const
{
  float fFrameWidth = m_textureId->width / static_cast<float>(m_horizontalFrames);
  float fFrameHeight = m_textureId->height / static_cast<float>(m_verticalFrames);
  return Vec2(fFrameWidth * m_scale, fFrameHeight * m_scale);
}

const Vec2& CSpriteComponent::GetPivot() const
{
  return m_pivot;
}

void CSpriteComponent::SetPivot(const Vec2& _rNewPivot)
{
  m_pivot = _rNewPivot;
}

float CSpriteComponent::GetHorizontalFrames() const
{
  return static_cast<float>(m_horizontalFrames);
}

float CSpriteComponent::GetVerticalFrames() const
{
  return static_cast<float>(m_verticalFrames);
}

int CSpriteComponent::GetFPS() const
{
  return static_cast<int>(m_fps);
}

void CSpriteComponent::SetFPS(int _iFps)
{
  m_fps = static_cast<float>(_iFps);
}

float CSpriteComponent::GetCurrentFrame() const
{
  return m_currentFrame;
}

void CSpriteComponent::SetCurrentFrame(int _iFrame)
{
  m_currentFrame = static_cast<float>(_iFrame);
}

void CSpriteComponent::SetReflexSprite(bool _reflexX, bool _reflexY)
{
  m_reflexSpriteX = _reflexX;
  m_reflexSpriteY = _reflexY;
}

void CSpriteComponent::Update(float _fDeltaTime)
{
  if (IsActive())
  {
    // Internal update (update current frame)
    int iTotalFrames = m_horizontalFrames * m_verticalFrames;
    m_currentFrame += m_fps * _fDeltaTime;
    if (static_cast<int>(m_currentFrame) >= iTotalFrames)
    {
      m_currentFrame = fmodf(m_currentFrame, static_cast<float>(iTotalFrames));
    }
    while (m_currentFrame < 0)
      m_currentFrame += static_cast<float>(iTotalFrames);
  }
}

void CSpriteComponent::Render() const
{
  if (m_textureId)
  {
    // Get UV coords from current frame
    float fDeltaHorFrame = 1.f / static_cast<float>(m_horizontalFrames);
    float fDeltaVerFrame = 1.f / static_cast<float>(m_verticalFrames);
    int iCurrentFrame = static_cast<int>(m_currentFrame);
    float fu0 = fmodf(static_cast<float>(iCurrentFrame) * fDeltaHorFrame, static_cast<float>(m_horizontalFrames));
    float fv0 = fDeltaVerFrame * static_cast<float>(iCurrentFrame / m_horizontalFrames);
    float fu1 = fu0 + fDeltaHorFrame;
    float fv1 = fv0 + fDeltaVerFrame;

    if (m_reflexSpriteX)
    {
      float backup = fu0;
      fu0 = fu1;
      fu1 = backup;
    }
    if (m_reflexSpriteY)
    {
      float backup = fv0;
      fv0 = fv1;
      fv1 = backup;
    }

    // Get position from Transform component
    CTransformComponent* transformComponent = GetOwner()->GetComponent<CTransformComponent>();
    Vec2 position(transformComponent->GetPosition());

    // Set draw mode
    CRenderEngine::SetBlend(m_blendMode);
    CRenderEngine::SetColor(m_color[0], m_color[1], m_color[2], m_color[3]);

    // Prepare draw data
    CRenderEngine::SImageRenderData imageData;
    imageData.m_tex = m_textureId;
    imageData.m_position = position;
    imageData.m_pivot = m_pivot;
    imageData.m_rotation = m_rotation;
    imageData.m_size.SetX(m_textureId->width * fDeltaHorFrame * m_scale);
    imageData.m_size.SetY(m_textureId->height * fDeltaVerFrame * m_scale);
    imageData.m_uv[0] = Vec2(fu0, fv0);
    imageData.m_uv[1] = Vec2(fu1, fv1);
    // Draw the sprite
    CRenderEngine::RenderImage(imageData);
  }
  else PRINT_WARNING("Sprite no inicializado");
}
