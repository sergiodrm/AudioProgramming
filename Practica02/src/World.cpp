
#include "World.h"

#include "CameraComponent.h"
#include "MacroUtility.h"
#include "Collider.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"

#pragma warning(disable : 4172)


void CWorld::Update(float DeltaTime)
{
  // Render backgrounds
  for (CGameObject* iterator : m_backgrounds)
  {
    iterator->Update(DeltaTime);
  }

  // Update game objects
  for (CGameObject* iterator : m_gameObjects)
  {
    iterator->Update(DeltaTime);
  }
}

void CWorld::RenderWorld(const Vec2& screenSize) const
{
  // Render backgrounds
  for (CGameObject* iterator : m_backgrounds)
  {
    CRenderComponent* renderComponent = iterator->GetComponent<CRenderComponent>();
    if (renderComponent != nullptr)
    {
      renderComponent->Render();
    }
  }

  // Render map
  if (m_map != nullptr) 
    m_map->Draw();

  // Render game objects (those which can be rendered)
  for (CGameObject* iterator : m_gameObjects)
  {
    CRenderComponent* renderComponent = iterator->GetComponent<CRenderComponent>();
    if (renderComponent != nullptr)
    {
      renderComponent->Render();
    }
  }
}

void CWorld::AddGameObject(CGameObject* _gameObject)
{
  ensure(_gameObject != nullptr);
  m_gameObjects.push_back(_gameObject);
  print_log("Total game objects in memory: %d", m_gameObjects.size() + m_backgrounds.size());
}

void CWorld::RemoveGameObject(CGameObject* _gameObject)
{
  ensure(_gameObject != nullptr);
  for (std::vector<CGameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
  {
    if (*it == _gameObject)
    {
      m_gameObjects.erase(it);
      return;
    }
  }
}

void CWorld::AddBackground(CGameObject* _background)
{
  ensure(_background != nullptr);
  m_backgrounds.push_back(_background);
  print_log("Total game objects in memory: %d", m_gameObjects.size() + m_backgrounds.size());
}

void CWorld::RemoveBackground(CGameObject* _background)
{
  ensure(_background != nullptr);
  for (std::vector<CGameObject*>::iterator it = m_backgrounds.begin(); it != m_backgrounds.end(); ++it)
  {
    if (*it == _background)
    {
      m_backgrounds.erase(it);
      return;
    }
  }
}


const Vec2& CWorld::GetCurrentCameraPosition() const
{
  for (CGameObject* iterator : m_gameObjects)
  {
    CCameraComponent* cameraComponent = iterator->GetComponent<CCameraComponent>();
    if (cameraComponent != nullptr && cameraComponent->IsCameraActive())
    {
      return iterator->GetComponent<CTransformComponent>()->GetPosition();
    }
  }
  return Vec2();
}

void CWorld::Clear()
{
  print_log("Removing game objects in memory: %d", m_gameObjects.size() + m_backgrounds.size());
  for (CGameObject* iterator : m_backgrounds)
  {
    CGameObject::Destroy(iterator);
  }
  for (CGameObject* iterator : m_gameObjects)
  {
    CGameObject::Destroy(iterator);
  }
}

void CWorld::Init()
{
  CreateSingleton();
  CRenderEngine::GetInstance().BindDrawCallback<CWorld, &CWorld::RenderWorld>(&GetInstance());
  CRenderEngine::GetInstance().SetClearColor(0.1f, 0.1f, 0.1f);
}

CWorld& CWorld::GetInstance()
{
  return GetSingletonInstance();
}

void CWorld::Shutdown()
{
  GetInstance().Clear();
  DestroySingleton();
}


