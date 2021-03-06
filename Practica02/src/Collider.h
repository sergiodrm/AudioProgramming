#pragma once

#include "Vec2.h"
#include <memory>

#define PIXELS_NUMBER_CHANNELS  4
#define PIXELS_ALPHA_THRESHOLD  0
#define PIXELS_CHANNEL_RED      0
#define PIXELS_CHANNEL_GREEN    1
#define PIXELS_CHANNEL_BLUE     2
#define PIXELS_CHANNEL_ALPHA    3

// Forward declaration
//class Vec2;

// Typedef
typedef unsigned char uint8_t;

// ***********************************************************************************
// BASE CLASS: Collider
// ***********************************************************************************

class CCollider
{
protected:
  typedef CCollider Super;

  // Atributes --------------------------------------------------------

protected:

  Vec2 m_vPosition;
  float m_tColor[PIXELS_NUMBER_CHANNELS];


  // Methods --------------------------------------------------------

public:

  explicit CCollider();
  explicit CCollider(const Vec2& _rPosition);
  virtual ~CCollider() {}

  Vec2 GetPosition() const;
  void SetPosition(const Vec2& _rNewPosition);
  void SetColor(float _fR, float _fG, float _fB, float _fA);

  virtual void Render(const Vec2&) const = 0;

  virtual bool Collides(const CCollider& _rOther) const = 0;
  virtual bool Collides(const Vec2& _rCirclePos, float _fRadius) const = 0;
  virtual bool Collides(const Vec2& _rRectPos, const Vec2& _rSize) const = 0;
  virtual bool Collides(const Vec2& _rPixelPos, const Vec2& _rPixelSize, const unsigned char* _pPixels) const = 0;

protected:

  bool CheckCircleCircle(const Vec2& _rPos1, float _fRadius1, const Vec2& _rPos2, float _fRadius2) const;
  bool CheckCircleRect(const Vec2& _rCirclePos, float _fRadius, const Vec2& _rRectPos, const Vec2& _rSize) const;
  bool CheckRectRect(const Vec2& _rPos1, const Vec2& _rSize1, const Vec2& _rPos2, const Vec2& _rSize2) const;
  bool CheckCirclePixels(const Vec2& _rCirclePos, float _fRadius, const Vec2& _rPixelPos, const Vec2& _rPixelSize, const uint8_t* _pPixels) const;
  bool CheckPixelsPixels(
    const Vec2& _rPos1, const Vec2& _rPixelSize1, const uint8_t* _pPixel1,
    const Vec2& _rPos2, const Vec2& _rPixelSize2, const uint8_t* _pPixel2
  ) const;
  bool CheckPixelsRect(
    const Vec2& _rPixelsPos, const Vec2& _rPixelsSize, const uint8_t* _pPixels,
    const Vec2& _rRectPos, const Vec2& _rRectSize
  ) const;

private:

  unsigned int GetIndexFromPixel(const Vec2& _rPixelInitialPos, const Vec2& _rPixelSize, const Vec2& _rPixelPosColliding) const;
  bool GetCollisionRectangle(const Vec2& _rRectPos1, const Vec2& _rSize1, const Vec2& _rRectPos2, const Vec2& _rSize2, Vec2& rRectCollisionPos_, Vec2& rRectCollisionSize_) const;

};


// ***********************************************************************************
// DERIVED CLASS: Circle collider
// ***********************************************************************************

class CCircleCollider : public CCollider
{
public:

  explicit CCircleCollider();
  explicit CCircleCollider(const Vec2& _rPosition, float _fRadius);

  float GetRadius() const;
  void SetRadius(float _fRadius);

  virtual void Render(const Vec2&) const override;

  virtual bool Collides(const CCollider& _rOther) const override;
  virtual bool Collides(const Vec2& _rCirclePos, float _fRadius) const override;
  virtual bool Collides(const Vec2& _rRectPos, const Vec2& _rSize) const override;
  virtual bool Collides(const Vec2& _rPixelPos, const Vec2& _rPixelSize, const uint8_t* _pPixels) const override;
  
protected:

  float m_fRadius;
};


// ***********************************************************************************
// DERIVED CLASS: Rect collider
// ***********************************************************************************

class CRectCollider : public CCollider
{
public:

  explicit CRectCollider();
  explicit CRectCollider(const Vec2& _rPosition, const Vec2& _rSize);

  Vec2 GetSize() const;
  void SetSize(const Vec2& _rSize);

  virtual void Render(const Vec2&) const override;

  virtual bool Collides(const CCollider& _rOther) const override;
  virtual bool Collides(const Vec2& _rCirclePos, float _fRadius) const override;
  virtual bool Collides(const Vec2& _rRectPos, const Vec2& _rSize) const override;
  virtual bool Collides(const Vec2& _rPixelPos, const Vec2& _rPixelSize, const uint8_t* _pPixels) const override;
  
protected:

  Vec2 m_vSize;

};


// ***********************************************************************************
// DERIVED CLASS: Pixels collider
// ***********************************************************************************

class CPixelsCollider : public CCollider
{
public:

  explicit CPixelsCollider();
  explicit CPixelsCollider(const Vec2& _rPosition, const Vec2& _rSize, uint8_t* _pPixels);

  Vec2 GetSize() const;
  void SetSize(const Vec2& _rSize);
  const uint8_t* GetPixels() const;
  void SetPixels(uint8_t* _pNewPixels);

  virtual void Render(const Vec2&) const override;

  virtual bool Collides(const CCollider& _rOther) const override;
  virtual bool Collides(const Vec2& _rCirclePos, float _fRadius) const override;
  virtual bool Collides(const Vec2& _rRectPos, const Vec2& _rSize) const override;
  virtual bool Collides(const Vec2& _rPixelPos, const Vec2& _rPixelSize, const uint8_t* _pPixels) const override;
  
protected:

  Vec2 m_vSize;

  uint8_t* m_pPixels;

};