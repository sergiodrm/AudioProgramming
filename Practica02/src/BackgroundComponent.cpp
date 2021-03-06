#include "BackgroundComponent.h"


#include "GameObject.h"
#include "RenderEngine.h"
#include "World.h"

CBackgroundComponent::CBackgroundComponent()
  : CSpriteComponent(), m_scrollRatio(1.f), m_scrollSpeed(Vec2(0.f, 0.f)),
    m_uv{Vec2(0.f, 0.f), Vec2(1.f, 1.f)}
{}

void CBackgroundComponent::Update(float _deltaTime)
{
  if (IsActive() && GetTexture() != nullptr)
  {
    float deltaU = _deltaTime * m_scrollSpeed.GetX() / static_cast<float>(GetTexture()->width);
    float deltaV = _deltaTime * m_scrollSpeed.GetY() / static_cast<float>(GetTexture()->height);
    m_uv[0].SetX(m_uv[0].GetX() + deltaU);
    m_uv[0].SetY(m_uv[0].GetY() + deltaV);
    m_uv[1].SetX(m_uv[1].GetX() + deltaU);
    m_uv[1].SetY(m_uv[1].GetY() + deltaV);
  }
}

void CBackgroundComponent::Render() const
{
  if (IsActive())
  {
    ensure(m_textureId != nullptr);
    // Set render status
    CRenderEngine::SetBlend(BLEND_ALPHA);
    CRenderEngine::SetColor(1.f, 1.f, 1.f, 1.f);

    // Calculate uvs
    float fScaleX = CWorld::GetInstance().GetMap()->GetSize().GetX() / static_cast<float>(m_textureId->width);
    float fScaleY = CWorld::GetInstance().GetMap()->GetSize().GetY() / static_cast<float>(m_textureId->height);
    float u0 = m_uv[0].GetX() * fScaleX;
    float v0 = m_uv[0].GetY() * fScaleY;
    float u1 = m_uv[1].GetX() * fScaleX;
    float v1 = m_uv[1].GetY() * fScaleY;

    // Prepare image render data
    CRenderEngine::SImageRenderData imageRenderData;
    imageRenderData.m_tex = m_textureId;
    imageRenderData.m_rotation = 0.f;
    imageRenderData.m_pivot = Vec2(0.f, 0.f);
    imageRenderData.m_position.SetX(CWorld::GetInstance().GetCurrentCameraPosition().GetX() * (1.f - m_scrollRatio));
    imageRenderData.m_position.SetY(CWorld::GetInstance().GetCurrentCameraPosition().GetY() * (1.f - m_scrollRatio));
    imageRenderData.m_size.SetX(static_cast<float>(m_textureId->width) * Math::Abs<float>(u1 - u0));
    imageRenderData.m_size.SetY(static_cast<float>(m_textureId->height) * Math::Abs<float>(v1 - v0));
    imageRenderData.m_uv[0] = Vec2(u0, v0);
    imageRenderData.m_uv[1] = Vec2(u1, v1);
    
    // Send data to render engine
    CRenderEngine::RenderImage(imageRenderData);
  }
}

