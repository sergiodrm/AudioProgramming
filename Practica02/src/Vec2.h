#pragma once


namespace Math
{
  constexpr double M_PI = 3.14159265358979323846;
  constexpr double M_PI_2 = 1.57079632679;
  constexpr double M_2_PI = 6.28318530718;

  bool IsNearlyEqual(float _fValue1, float _fValue2, float _fTolerance = 1.0e-4);

  template <typename T>
  T Max(T _value1, T _value2) { return _value1 > _value2 ? _value1 : _value2; }

  template <typename T>
  T Min(T _value1, T _value2) { return _value1 < _value2 ? _value1 : _value2; }

  template <typename T>
  T Clamp(T _value, T _min, T _max)
  {
    return (_value >= _min && _value <= _max) ? _value : (_value < _min) ? _min : _max;
  }

  template <typename T>
  T Abs(T _value) { return _value > 0 ? _value : -_value; }

  template <typename T>
  bool InRange(T _value, T _min, T _max, bool _minIncluded = true, bool _maxIncluded = true)
  {
    if (_minIncluded && _maxIncluded)
    {
      return _value >= _min && _value <= _max;
    }
    if (_minIncluded)
    {
      return _value >= _min && _value < _max;
    }
    if (_maxIncluded)
    {
      return _value > _min && _value <= _max;
    }
    return _value > _min && _value < _max;
  }

  inline float Sign(float _fValue) { return _fValue >= 0 ? 1.f : -1.f; }

  inline float Rad2Deg(float _fRad)
  {
    return _fRad * 180.f / static_cast<float>(M_PI);
  }

  inline float Deg2Rad(float _fDeg)
  {
    return _fDeg * static_cast<float>(M_PI) / 180.f;
  }
}

class Vec2
{
public:

  // Constructores y destructor ------------------

  Vec2();
  Vec2(float _fX, float _fY);

  // TODO: constructor copia y con move semantics si el de por defecto no sirve
  //Vec2(const Vec2& _rOther);
  //Vec2(Vec2&& _rOther);
  //~Vec2();

  // Operadores ----------------------------------

  // TODO: si hace falta que no sea el de por defecto...
  //const Vec2& operator=(const Vec2& _rOther);
  //const Vec2& operator=(Vec2&& _rOther);

  Vec2 operator+(const Vec2& _rOther);
  Vec2 operator+(float _fValue);
  Vec2& operator+=(const Vec2& _rOther);
  Vec2& operator+=(float _fValue);
  Vec2 operator-(const Vec2& _rOther);
  Vec2 operator-(float _fValue);
  Vec2& operator-=(const Vec2& _rOther);
  Vec2& operator-=(float _fValue);
  Vec2 operator*(const Vec2& _rOther);
  Vec2 operator*(float _fValue);
  Vec2& operator*=(const Vec2& _rOther);
  Vec2& operator*=(float _fValue);
  Vec2 operator/(const Vec2& _rOther);
  Vec2 operator/(float _fValue);
  Vec2& operator/=(const Vec2& _rOther);
  Vec2& operator/=(float _fValue);

  // Metodos -------------------------------------

  float GetX() const { return m_fX; }
  float GetY() const { return m_fY; }
  void SetX(float _fX) { m_fX = _fX; }
  void SetY(float _fY) { m_fY = _fY; }

  Vec2 GetAbs() const;
  Vec2 GetNormal() const;

  float Dot(const Vec2& _rOther) const;
  static float Dot(const Vec2& _rV1, const Vec2& _rV2);

  float Angle(const Vec2& _rOther) const;
  static float Angle(const Vec2& _rV1, const Vec2& _rV2);

  float Distance(const Vec2& _rOther) const;
  static float Distance(const Vec2& _rV1, const Vec2& _rV2);

  float Length() const;
  static float Length(const Vec2& _rVector);

  bool IsNormalized() const;
  void Normalize();

private:

  // Atributos -----------------------------------

  float m_fX;
  float m_fY;
};

Vec2 operator+(const Vec2& _rVector, float _fScalar);
Vec2 operator+(const Vec2& _rVector1, const Vec2& _rVector2);
Vec2 operator-(const Vec2& _rVector1, const Vec2& _rVector2);
Vec2 operator-(const Vec2& _rVector, float _fScalar);
Vec2 operator*(const Vec2& _rVector, float _fScalar);
Vec2 operator/(const Vec2& _rVector, float _fScalar);
bool operator==(const Vec2& _rVector1, const Vec2& _rVector2);
bool operator!=(const Vec2& _rVector1, const Vec2& _rVector2);
