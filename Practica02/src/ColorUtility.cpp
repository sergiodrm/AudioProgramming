#include "ColorUtility.h"

SColor::SColor(float _fR, float _fG, float _fB, float _fA)
{ 
	Init(_fR, _fG, _fB); 
}

SColor::SColor(DefaultColor _eColor)
{
	switch (_eColor)
	{
	case DefaultColor::White: Init(1.f, 1.f, 1.f); break;
	case DefaultColor::Red:		Init(1.f, 0.f, 0.f); break;
	case DefaultColor::Green: Init(0.f, 1.f, 0.f); break;
	case DefaultColor::Blue:	Init(0.f, 0.f, 1.f); break;
	case DefaultColor::Black: Init(0.f, 0.f, 0.f); break;
	}
}

void SColor::Init(float _fR, float _fG, float _fB, float _fA)
{
	R = _fR;
	G = _fG;
	B = _fB;
	A = _fA;
}