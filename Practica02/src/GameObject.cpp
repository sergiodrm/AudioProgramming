#include "GameObject.h"
#include "MacroUtility.h"
#include "TransformComponent.h"
#include "World.h"

CGameObject* CGameObject::Create()
{
  // Create
  CGameObject* gameObject = new CGameObject();
  ensure(gameObject != nullptr);
  // Initialize
  gameObject->OnCreate();
  // Set default component
  gameObject->AddComponent<CTransformComponent>();

  CWorld::GetInstance().AddGameObject(gameObject);
  return gameObject;
}

void CGameObject::Destroy(CGameObject* _gameObject)
{
  ensure(_gameObject != nullptr);
  _gameObject->OnDestroy();
  delete _gameObject;
}

void CGameObject::OnCreate()
{}

void CGameObject::OnDestroy()
{
  for (CComponent* iterator : m_components)
  {
    CComponent::Destroy(iterator);
  }
  m_components.clear();
}

void CGameObject::Active()
{
  m_bActive = true;
  for (CComponent* iterator : m_components)
  {
    iterator->Active();
  }
}

void CGameObject::Deactive()
{
  m_bActive = false;
  for (CComponent* iterator : m_components)
  {
    iterator->Deactive();
  }
}

void CGameObject::Update(float _deltaTime)
{
  if (IsActive())
  {
    for (CComponent* iterator : m_components)
    {
      iterator->Update(_deltaTime);
    }
  }
}

CGameObject::CGameObject()
  : m_bActive(false)
{
  m_components.reserve(4);
}
