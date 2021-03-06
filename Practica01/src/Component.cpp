#include "Component.h"


void CComponent::Destroy(CComponent* _component)
{
  ensure(_component != nullptr);
  _component->OnDestroy();
  delete _component;
}

void CComponent::OnCreate()
{}

void CComponent::OnDestroy()
{}

void CComponent::Active()
{
  m_bActive = true; 
}

void CComponent::Deactive()
{
  m_bActive = false;
}

CComponent::CComponent()
  : m_owner(nullptr), m_bActive(false)
{}

CComponent::~CComponent()
{}
