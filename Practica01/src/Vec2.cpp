#include "Vec2.h"

#include <math.h>

// ************************************************************************
// MATH
// ************************************************************************

bool Math::IsNearlyEqual(float _fValue1, float _fValue2, float _fTolerance)
{
  return _fValue1 <= _fValue2 + _fTolerance &&
    _fValue1 >= _fValue2 - _fTolerance;
}


// ************************************************************************
// VEC2
// ************************************************************************

// Constructores --------------------------------------

Vec2::Vec2() 
  : m_fX(0.f), m_fY(0.f)
{}

Vec2::Vec2(float _fX, float _fY)
  : m_fX(_fX), m_fY(_fY)
{}

// Operadores --------------------------------------

Vec2 Vec2::operator+(const Vec2& _rOther)
{
  return Vec2(m_fX + _rOther.m_fX, m_fY + _rOther.m_fY);
}

Vec2 Vec2::operator+(float _fValue)
{
  return Vec2(m_fX + _fValue, m_fY + _fValue);
}

Vec2& Vec2::operator+=(const Vec2& _rOther)
{
  m_fX += _rOther.m_fX;
  m_fY += _rOther.m_fY;
  return *this;
}

Vec2& Vec2::operator+=(float _fValue)
{
  m_fX += _fValue;
  m_fY += _fValue;
  return *this;
}

Vec2 Vec2::operator-(const Vec2& _rOther)
{
  return Vec2(m_fX - _rOther.m_fX, m_fY - _rOther.m_fY);
}

Vec2 Vec2::operator-(float _fValue)
{
  return Vec2(m_fX - _fValue, m_fY - _fValue);
}

Vec2& Vec2::operator-=(const Vec2& _rOther)
{
  m_fX -= _rOther.m_fX;
  m_fY -= _rOther.m_fY;
  return *this;
}

Vec2& Vec2::operator-=(float _fValue)
{
  m_fX -= _fValue;
  m_fY -= _fValue;
  return *this;
}

Vec2 Vec2::operator*(const Vec2& _rOther)
{
  return Vec2(m_fX * _rOther.m_fX, m_fY * _rOther.m_fY);
}

Vec2 Vec2::operator*(float _fValue)
{
  return Vec2(m_fX * _fValue, m_fY * _fValue);
}

Vec2& Vec2::operator*=(const Vec2& _rOther)
{
  m_fX *= _rOther.m_fX;
  m_fY *= _rOther.m_fY;
  return *this;
}

Vec2& Vec2::operator*=(float _fValue)
{
  m_fX *= _fValue;
  m_fY *= _fValue;
  return *this;
}

Vec2 Vec2::operator/(const Vec2& _rOther)
{
  return Vec2(m_fX / _rOther.m_fX, m_fY / _rOther.m_fY);
}

Vec2 Vec2::operator/(float _fValue)
{
  return Vec2(m_fX / _fValue, m_fY / _fValue);
}

Vec2& Vec2::operator/=(const Vec2& _rOther)
{
  m_fX /= _rOther.m_fX;
  m_fY /= _rOther.m_fY;
  return *this;
}

Vec2& Vec2::operator/=(float _fValue)
{
  m_fX /= _fValue;
  m_fY /= _fValue;
  return *this;
}

// Metodos -----------------------------------------------------

Vec2 Vec2::GetAbs() const
{
  return Vec2(fabsf(m_fX), fabsf(m_fY));
}

Vec2 Vec2::GetNormal() const
{
  return Vec2(-m_fY, m_fX);
}

float Vec2::Dot(const Vec2& _rOther) const
{
  return m_fX * _rOther.m_fX + m_fY * _rOther.m_fY;
}

float Vec2::Dot(const Vec2& _rV1, const Vec2& _rV2)
{
  return _rV1.Dot(_rV2);
}

float Vec2::Angle(const Vec2& _rOther) const
{
  //return Math::Deg2Rad(acosf(Dot(_rOther) / (Length() * _rOther.Length())));
  //return Math::Rad2Deg(atan2f(_rOther.m_fY - m_fY, _rOther.m_fX - m_fX));
  return Math::Rad2Deg(atan2f(_rOther.m_fY, _rOther.m_fX) - atan2f(m_fY, m_fX));
}

float Vec2::Angle(const Vec2& _rV1, const Vec2& _rV2)
{
  return _rV1.Angle(_rV2);
}

float Vec2::Distance(const Vec2& _rOther) const
{
  Vec2 vSubs(m_fX - _rOther.m_fX, m_fY - _rOther.m_fY);
  return vSubs.Length();
}

float Vec2::Distance(const Vec2& _rV1, const Vec2& _rV2)
{
  return _rV1.Distance(_rV2);
}

float Vec2::Length() const
{
  return sqrtf(powf(m_fX, 2.f) + powf(m_fY, 2.f));
}

float Vec2::Length(const Vec2& _rVector)
{
  return _rVector.Length();
}

bool Vec2::IsNormalized() const
{
  return Math::IsNearlyEqual(Length(), 1.f);
}

void Vec2::Normalize()
{
  float fLength = Length();
  m_fX /= fLength;
  m_fY /= fLength;
}

Vec2 operator+(const Vec2& _rVector, float _fScalar)          { return Vec2(_rVector.GetX() + _fScalar, _rVector.GetY() + _fScalar); }
Vec2 operator+(const Vec2& _rVector1, const Vec2& _rVector2)  { return Vec2(_rVector1.GetX() + _rVector2.GetX(), _rVector1.GetY() + _rVector2.GetY()); }
Vec2 operator-(const Vec2& _rVector1, const Vec2& _rVector2)  { return Vec2(_rVector1.GetX() - _rVector2.GetX(), _rVector1.GetY() - _rVector2.GetY()); }
Vec2 operator-(const Vec2& _rVector, float _fScalar)          { return Vec2(_rVector.GetX() - _fScalar, _rVector.GetY() - _fScalar); }
Vec2 operator*(const Vec2& _rVector, float _fScalar)          { return Vec2(_rVector.GetX() * _fScalar, _rVector.GetY() * _fScalar); }
Vec2 operator/(const Vec2& _rVector, float _fScalar)          { return Vec2(_rVector.GetX() / _fScalar, _rVector.GetY() / _fScalar); }
bool operator==(const Vec2& _rVector1, const Vec2& _rVector2) { return Math::IsNearlyEqual(_rVector1.GetX(), _rVector2.GetX()) && Math::IsNearlyEqual(_rVector1.GetY(), _rVector2.GetY());}
bool operator!=(const Vec2& _rVector1, const Vec2& _rVector2) { return !(_rVector1 == _rVector2); }
