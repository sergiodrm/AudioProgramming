#pragma once

#include "MacroUtility.h"

// Forward declaration
class CGameObject;

/**
 *    Component
 */
class CComponent
{
  DECLARE_BASE_CLASS(CComponent)
public:

  template <typename C> static C* Create(CGameObject* _owner);
  static void Destroy(CComponent* _component);

  virtual void OnCreate();
  virtual void OnDestroy();
  virtual void Active();
  virtual void Deactive();
  virtual bool IsActive() const;

  virtual void Update(float _deltaTime) = 0;

  CGameObject* GetOwner() const;

protected:
  CComponent();
  virtual ~CComponent();

  CGameObject* m_owner;
  bool m_bActive;
};

/**
 *    Component - Inlines definition
 */
inline CGameObject* CComponent::GetOwner() const  { return m_owner; }
inline bool CComponent::IsActive() const          { return m_bActive; }


/**
 *    Component - Templates definition
 */
template <typename C>
C* CComponent::Create(CGameObject* _owner)
{
  ensure(_owner != nullptr);
  C* component = new C();
  component->m_owner = _owner;
  component->OnCreate();
  return component;
}

