#pragma once

#include <vector>
#include "Component.h"

// Forward declaration

/**
 *    Game object
 */
class CGameObject
{
public:

  /**
   * Create & Destroy static methods to control how it should be created (and destroyed).
   */
  static CGameObject* Create();
  static void Destroy(CGameObject* _gameObject);

  /**
   * @brief It'll be called when the instance is created.
   */
  void OnCreate();
  /**
   * @brief It'll be called when the instance is destroyed.
   */
  void OnDestroy();

  /**
   * @brief Active game object and all its components.
   */
  void Active();
  /**
   * @brief Deactive game object and all its components.
   */
  void Deactive();
  /**
   * @brief ...
   */
  bool IsActive() const;

  /**
   * @brief It'll be called at least once per frame.
   */
  void Update(float _deltaTime);

  /**
   * @brief Method to add a component into the instance.
   */
  template <typename C> C* AddComponent();
  /**
   * @brief It returns a component of class C if it exists in the instance.
   */
  template <typename C> C* GetComponent() const;
  /**
   * @brief Destroy certain component.
   */
  template <typename C> void DestroyComponent();

private:

  /**
   * Private constructor to avoid creating game objects outside -> (Use CGameObject::Create() pls)
   */
  CGameObject();

  std::vector<CComponent*> m_components;
  bool m_bActive;
};

/**
 *    Game object - Inlines definition
 */
inline bool CGameObject::IsActive() const { return m_bActive; }


/**
 *    Game object - templates definition
 */

template <typename C>
C* CGameObject::AddComponent()
{
  C* component = CComponent::Create<C>(this);
  m_components.push_back(component);
  return component;
}

template <typename C>
C* CGameObject::GetComponent() const
{
  for (CComponent* iterator : m_components)
  {
    C* desiredComponent = dynamic_cast<C*>(iterator);
    if (desiredComponent != nullptr)
      return desiredComponent;
  }
  return nullptr;
}

template <typename C>
void CGameObject::DestroyComponent()
{
  for (std::vector<CComponent*>::iterator iterator = m_components.begin(); iterator != m_components.end(); ++iterator)
  {
    C* component = dynamic_cast<C*>(*iterator);
    if (component != nullptr)
    {
      m_components.erase(iterator);
      CComponent::Destroy(component);
      return;
    }
  }
}


