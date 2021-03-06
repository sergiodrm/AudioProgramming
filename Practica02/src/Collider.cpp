
#include "Collider.h"
#include "litegfx.h"
#include "glfw3.h"
#include "RenderEngine.h"
#include "MacroUtility.h"




CCollider::CCollider()
  : m_vPosition(Vec2(0.f, 0.f))
{
  m_tColor[PIXELS_CHANNEL_RED] = 0.f;
  m_tColor[PIXELS_CHANNEL_GREEN] = 1.f;
  m_tColor[PIXELS_CHANNEL_BLUE] = 0.f;
  m_tColor[PIXELS_CHANNEL_ALPHA] = 1.f;
}

CCollider::CCollider(const Vec2& _rPosition)
  : m_vPosition(_rPosition)
{
  m_tColor[PIXELS_CHANNEL_RED] = 0.f;
  m_tColor[PIXELS_CHANNEL_GREEN] = 1.f;
  m_tColor[PIXELS_CHANNEL_BLUE] = 0.f;
  m_tColor[PIXELS_CHANNEL_ALPHA] = 1.f;
}

Vec2 CCollider::GetPosition() const
{
  return m_vPosition;
}

void CCollider::SetPosition(const Vec2& _rNewPosition)
{
  m_vPosition = _rNewPosition;
}

void CCollider::SetColor(float _fR, float _fG, float _fB, float _fA)
{
  m_tColor[PIXELS_CHANNEL_RED] = _fR;
  m_tColor[PIXELS_CHANNEL_GREEN] = _fG;
  m_tColor[PIXELS_CHANNEL_BLUE] = _fB;
  m_tColor[PIXELS_CHANNEL_ALPHA] = _fA;
}

bool CCollider::CheckCircleCircle(const Vec2& _rPos1, float _fRadius1, const Vec2& _rPos2, float _fRadius2) const
{
  Vec2 diff(_rPos2.GetX() - _rPos1.GetX(), _rPos2.GetY() - _rPos1.GetY());
  return diff.Length() <= _fRadius1 + _fRadius2;
}

bool CCollider::CheckCircleRect(const Vec2& _rCirclePos, float _fRadius, const Vec2& _rRectPos, const Vec2& _rSize) const
{
  float fClosestX = Math::Clamp(_rCirclePos.GetX(), _rRectPos.GetX(), _rRectPos.GetX() + _rSize.GetX());
  float fClosestY = Math::Clamp(_rCirclePos.GetY(), _rRectPos.GetY(), _rRectPos.GetY() + _rSize.GetY());
  float fDistanceRectCircle = Vec2::Length(Vec2(fClosestX - _rCirclePos.GetX(), fClosestY - _rCirclePos.GetY()));
  return fDistanceRectCircle <= _fRadius;
}

bool CCollider::CheckRectRect(const Vec2& _rPos1, const Vec2& _rSize1, const Vec2& _rPos2, const Vec2& _rSize2) const
{
  bool collides = false;
  // Compruebo si la x del primer rect esta en los limites del segundo rect o viceversa
  if (Math::InRange(_rPos1.GetX(), _rPos2.GetX(), _rPos2.GetX() + _rSize2.GetX()) || 
    Math::InRange(_rPos2.GetX(), _rPos1.GetX(), _rPos1.GetX() + _rSize1.GetX()))
  {
    // Si lo esta, comprobar si la coordenada y tambien esta en los limites del rect2 o viceversa
    if (Math::InRange(_rPos1.GetY(), _rPos2.GetY(), _rPos2.GetY() + _rSize2.GetY()) ||
      Math::InRange(_rPos2.GetY(), _rPos1.GetY(), _rPos1.GetY() + _rSize1.GetY()))
    {
      collides = true;
    }
  }
  return collides;
}

bool CCollider::CheckCirclePixels(const Vec2& _rCirclePos, float _fRadius, const Vec2& _rPixelPos, const Vec2& _rPixelSize, const uint8_t* _pPixels) const
{
  Vec2 vRectCollisionPos, vRectCollisionSize;
  if (!GetCollisionRectangle(_rCirclePos - _fRadius, Vec2(_fRadius * 2.f, _fRadius * 2.f), _rPixelPos, _rPixelSize, vRectCollisionPos, vRectCollisionSize))
    return false;

  for (unsigned int uRow = static_cast<unsigned int>(vRectCollisionPos.GetY()); uRow < static_cast<unsigned int>(vRectCollisionPos.GetY() + vRectCollisionSize.GetY()); ++uRow)
  {
    for (unsigned int uCol = static_cast<unsigned int>(vRectCollisionPos.GetX()); uCol < static_cast<unsigned int>(vRectCollisionPos.GetX() + vRectCollisionSize.GetX()); ++uCol)
    {
      unsigned int uIndex = GetIndexFromPixel(_rPixelPos, _rPixelSize, Vec2(static_cast<float>(uCol), static_cast<float>(uRow)));
      if (_pPixels[uIndex] > PIXELS_ALPHA_THRESHOLD)
      {
        Vec2 vDistanceCirclePixel(Vec2(static_cast<float>(uCol), static_cast<float>(uRow)) - _rCirclePos);
        if (vDistanceCirclePixel.Length() <= _fRadius)
        {
          // Colision!!!
          return true;
        }
      }
    }
  }
  // Ha habido colision entre los rectangulos exteriores pero no entre pixeles con alpha != 0
  return false;
}

bool CCollider::CheckPixelsPixels(const Vec2& _rPos1, const Vec2& _rPixelSize1, const uint8_t* _pPixel1, const Vec2& _rPos2, const Vec2& _rPixelSize2, const uint8_t* _pPixel2) const
{
  Vec2 vRectCollisionPos, vRectCollisionSize;
  if (!GetCollisionRectangle(_rPos1, _rPixelSize1, _rPos2, _rPixelSize2, vRectCollisionPos, vRectCollisionSize))
    return false;

  // Una vez obtenidas la posicion y dimension del rectangulo de colision, 
  // tratar a sus pixeles como si fuera una matriz y obtener el indice en el 
  // array de la textura para comparar los canales alpha.
  for (unsigned int uRow = static_cast<unsigned int>(vRectCollisionPos.GetY()); uRow < static_cast<unsigned int>(vRectCollisionPos.GetY() + vRectCollisionSize.GetY()); ++uRow)
  {
    for (unsigned int uCol = static_cast<unsigned int>(vRectCollisionPos.GetX()); uCol < static_cast<unsigned int>(vRectCollisionPos.GetX() + vRectCollisionSize.GetX()); ++uCol)
    {
      unsigned int uIndex1 = GetIndexFromPixel(_rPos1, _rPixelSize1, Vec2(static_cast<float>(uCol), static_cast<float>(uRow)));
      unsigned int uIndex2 = GetIndexFromPixel(_rPos2, _rPixelSize2, Vec2(static_cast<float>(uCol), static_cast<float>(uRow)));
      if (_pPixel1[uIndex1] > PIXELS_ALPHA_THRESHOLD && _pPixel2[uIndex2] > PIXELS_ALPHA_THRESHOLD)
      {
        // Colision!!!
        return true;
      }
    }
  }
  // Ha habido colision entre los rectangulos exteriores pero no entre pixeles con alpha != 0
  return false;
}

bool CCollider::CheckPixelsRect(const Vec2& _rPixelsPos, const Vec2& _rPixelsSize, const uint8_t* _pPixels, const Vec2& _rRectPos, const Vec2& _rRectSize) const
{
  Vec2 vRectCollisionPos, vRectCollisionSize;
  if (!GetCollisionRectangle(_rPixelsPos, _rPixelsSize, _rRectPos, _rRectSize, vRectCollisionPos, vRectCollisionSize))
    return false;

  for (unsigned int uRow = static_cast<unsigned int>(vRectCollisionPos.GetY()); uRow < static_cast<unsigned int>(vRectCollisionPos.GetY() + vRectCollisionSize.GetY()); ++uRow)
  {
    for (unsigned int uCol = static_cast<unsigned int>(vRectCollisionPos.GetX()); uCol < static_cast<unsigned int>(vRectCollisionPos.GetX() + vRectCollisionSize.GetX()); ++uCol)
    {
      unsigned int uIndex = GetIndexFromPixel(_rPixelsPos, _rPixelsSize, Vec2(static_cast<float>(uCol), static_cast<float>(uRow)));
      if (_pPixels[uIndex] > PIXELS_ALPHA_THRESHOLD)
      {
        // Colision!!!
        return true;
      }
    }
  }
  // Ha habido colision entre los rectangulos exteriores pero no entre pixeles con alpha != 0
  return false;
}

unsigned int CCollider::GetIndexFromPixel(const Vec2& _rPixelInitialPos, const Vec2& _rPixelSize, const Vec2& _rPixelPosColliding) const
{
  unsigned int uRow = static_cast<unsigned int>(_rPixelPosColliding.GetY() - _rPixelInitialPos.GetY());
  unsigned int uCol = static_cast<unsigned int>(_rPixelPosColliding.GetX() - _rPixelInitialPos.GetX());

  return (uRow * static_cast<unsigned int>(_rPixelSize.GetX()) + uCol) * PIXELS_NUMBER_CHANNELS + PIXELS_CHANNEL_ALPHA;
}

bool CCollider::GetCollisionRectangle(const Vec2& _rRectPos1, const Vec2& _rSize1, const Vec2& _rRectPos2, const Vec2& _rSize2, Vec2& rRectCollisionPos_, Vec2& rRectCollisionSize_) const
{
  // Primero comprobar la colision rect-rect
  if (!CheckRectRect(_rRectPos1, _rSize1, _rRectPos2, _rSize2))
    return false;

  // Obtener las coordenadas del pixel "mas profundo" en el rectangulo de colision
  unsigned int uRectCollisionX = static_cast<unsigned int>(Math::Max<float>(_rRectPos1.GetX(), _rRectPos2.GetX()));
  unsigned int uRectCollisionY = static_cast<unsigned int>(Math::Max<float>(_rRectPos1.GetY(), _rRectPos2.GetY()));

  // Obtener los limites del rectangulo de colision
  unsigned int uRectCollisionXLimit = static_cast<unsigned int>(Math::Min<float>(_rRectPos1.GetX() + _rSize1.GetX(), _rRectPos2.GetX() + _rSize2.GetX()));
  unsigned int uRectCollisionYLimit = static_cast<unsigned int>(Math::Min<float>(_rRectPos1.GetY() + _rSize1.GetY(), _rRectPos2.GetY() + _rSize2.GetY()));
  //CRenderEngine::GetInstance().fX = uRectCollisionX;
  //CRenderEngine::GetInstance().fY = uRectCollisionY;
  //CRenderEngine::GetInstance().width = uRectCollisionXLimit - uRectCollisionX;
  //CRenderEngine::GetInstance().height = uRectCollisionYLimit - uRectCollisionY;
  rRectCollisionPos_.SetX(static_cast<float>(uRectCollisionX));
  rRectCollisionPos_.SetY(static_cast<float>(uRectCollisionY));
  rRectCollisionSize_.SetX(static_cast<float>(uRectCollisionXLimit - uRectCollisionX));
  rRectCollisionSize_.SetY(static_cast<float>(uRectCollisionYLimit - uRectCollisionY));
  return true;
}



// ***********************************************************************************
// DERIVED CLASS: Circle collider
// ***********************************************************************************

CCircleCollider::CCircleCollider()
  : Super(), m_fRadius(0.f)
{
  
}

CCircleCollider::CCircleCollider(const Vec2& _rPosition, float _fRadius)
  : Super(_rPosition), m_fRadius(_fRadius)
{
}

float CCircleCollider::GetRadius() const
{
  return m_fRadius;
}

void CCircleCollider::SetRadius(float _fRadius)
{
  m_fRadius = _fRadius;
}

void CCircleCollider::Render(const Vec2&) const
{
  lgfx_setblend(BLEND_ALPHA);
  lgfx_setcolor(m_tColor[PIXELS_CHANNEL_RED], m_tColor[PIXELS_CHANNEL_BLUE], m_tColor[PIXELS_CHANNEL_GREEN], m_tColor[PIXELS_CHANNEL_ALPHA]);
  lgfx_drawoval(m_vPosition.GetX(), m_vPosition.GetY(), m_fRadius, m_fRadius);
}

bool CCircleCollider::Collides(const CCollider& _rOther) const
{
  // Call collides with circle of the other collider
  return _rOther.Collides(m_vPosition, m_fRadius);
}

bool CCircleCollider::Collides(const Vec2& _rCirclePos, float _fRadius) const
{
  return CheckCircleCircle(m_vPosition, m_fRadius, _rCirclePos, _fRadius);
}

bool CCircleCollider::Collides(const Vec2& _rRectPos, const Vec2& _rSize) const
{
  return CheckCircleRect(m_vPosition, m_fRadius, _rRectPos, _rSize);
}

bool CCircleCollider::Collides(const Vec2& _rPixelPos, const Vec2& _rPixelSize, const uint8_t* _pPixels) const
{
  return CheckCirclePixels(m_vPosition, m_fRadius, _rPixelPos, _rPixelSize, _pPixels);
}


// ***********************************************************************************
// DERIVED CLASS: Rect collider
// ***********************************************************************************

CRectCollider::CRectCollider()
  : Super(), m_vSize(Vec2(0.f, 0.f))
{}

CRectCollider::CRectCollider(const Vec2& _rPosition, const Vec2& _rSize)
  : Super(_rPosition), m_vSize(_rSize)
{}

Vec2 CRectCollider::GetSize() const
{
  return m_vSize;
}

void CRectCollider::SetSize(const Vec2& _rSize)
{
  m_vSize = _rSize;
}

void CRectCollider::Render(const Vec2&) const
{
  lgfx_setblend(BLEND_ALPHA);
  lgfx_setcolor(m_tColor[PIXELS_CHANNEL_RED], m_tColor[PIXELS_CHANNEL_BLUE], m_tColor[PIXELS_CHANNEL_GREEN], m_tColor[PIXELS_CHANNEL_ALPHA]);
  lgfx_drawrect(m_vPosition.GetX(), m_vPosition.GetY(), m_vSize.GetX(), m_vSize.GetY());
}

bool CRectCollider::Collides(const CCollider& _rOther) const
{
  return _rOther.Collides(m_vPosition, m_vSize);
}

bool CRectCollider::Collides(const Vec2& _rCirclePos, float _fRadius) const
{
  return CheckCircleRect(_rCirclePos, _fRadius, m_vPosition, m_vSize);
}

bool CRectCollider::Collides(const Vec2& _rRectPos, const Vec2& _rSize) const
{
  return CheckRectRect(m_vPosition, m_vSize, _rRectPos, _rSize);
}

bool CRectCollider::Collides(const Vec2& _rPixelPos, const Vec2& _rPixelSize, const uint8_t* _pPixels) const
{
  return CheckPixelsRect(_rPixelPos, _rPixelSize, _pPixels, m_vPosition, m_vSize);
}


// ***********************************************************************************
// DERIVED CLASS: Pixels collider
// ***********************************************************************************

CPixelsCollider::CPixelsCollider()
  : Super(), m_vSize(Vec2(0.f, 0.f)), m_pPixels(nullptr)
{}

CPixelsCollider::CPixelsCollider(const Vec2& _rPosition, const Vec2& _rSize, uint8_t* _pPixels)
  : Super(_rPosition), m_vSize(_rSize), m_pPixels(_pPixels)
{}

Vec2 CPixelsCollider::GetSize() const
{
  return m_vSize;
}

void CPixelsCollider::SetSize(const Vec2& _rSize)
{
  m_vSize = _rSize;
}

const uint8_t* CPixelsCollider::GetPixels() const
{
  return m_pPixels;
}

void CPixelsCollider::SetPixels(uint8_t* _pNewPixels)
{
  m_pPixels = _pNewPixels;
}

void CPixelsCollider::Render(const Vec2&) const
{
  lgfx_setblend(BLEND_ALPHA);
  lgfx_setcolor(m_tColor[PIXELS_CHANNEL_RED], m_tColor[PIXELS_CHANNEL_BLUE], m_tColor[PIXELS_CHANNEL_GREEN], m_tColor[PIXELS_CHANNEL_ALPHA]);
  lgfx_drawrect(m_vPosition.GetX(), m_vPosition.GetY(), m_vSize.GetX(), m_vSize.GetY());
}

bool CPixelsCollider::Collides(const CCollider& _rOther) const
{
  return _rOther.Collides(m_vPosition, m_vSize, m_pPixels);
}

bool CPixelsCollider::Collides(const Vec2& _rCirclePos, float _fRadius) const
{
  return CheckCirclePixels(_rCirclePos, _fRadius, m_vPosition, m_vSize, m_pPixels);
}

bool CPixelsCollider::Collides(const Vec2& _rRectPos, const Vec2& _rSize) const
{
  return CheckPixelsRect(m_vPosition, m_vSize, m_pPixels, _rRectPos, _rSize);
}

bool CPixelsCollider::Collides(const Vec2& _rPixelPos, const Vec2& _rPixelSize, const uint8_t* _pPixels) const
{
  return CheckPixelsPixels(m_vPosition, m_vSize, m_pPixels, _rPixelPos, _rPixelSize, _pPixels);
}

