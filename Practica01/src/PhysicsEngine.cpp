#include "PhysicsEngine.h"

#include "Collider.h"
#include "MacroUtility.h"
#include "RenderEngine.h"
#include "RigidBodyComponent.h"
#include "Utility.h"

#define DEBUG_COLLIDER 0


void CPhysicsEngine::Init()
{
  CreateSingleton();
  GetSingletonInstance().m_gravity = 9.8f;
}

CPhysicsEngine& CPhysicsEngine::GetInstance()
{
  return GetSingletonInstance();
}

void CPhysicsEngine::Shutdown()
{
  DestroySingleton();
}

void CPhysicsEngine::Update(float _deltaTime)
{}

void CPhysicsEngine::AddDynamicRigidBody(CRigidBodyComponent* _rigidBody)
{
  ensure(_rigidBody != nullptr);
  m_dynamicBodies.push_back(std::make_pair(0.f, _rigidBody));
}

void CPhysicsEngine::AddStaticRigidBody(CRigidBodyComponent* _rigidBody)
{
  ensure(_rigidBody != nullptr);
  m_staticBodies.push_back(_rigidBody);
}

void CPhysicsEngine::EraseRigidBody(CRigidBodyComponent* _rigidBody)
{
  for (std::vector<CRigidBodyComponent*>::iterator it = m_staticBodies.begin(); it != m_staticBodies.end(); ++it)
  {
    if (*it == _rigidBody)
    {
      m_staticBodies.erase(it);
      return;
    }
  }

  for (std::vector<std::pair<float, CRigidBodyComponent*>>::iterator dynamicIterator = m_dynamicBodies.begin();
    dynamicIterator != m_dynamicBodies.end();
    ++dynamicIterator)
  {
    if (dynamicIterator->second == _rigidBody)
    {
      m_dynamicBodies.erase(dynamicIterator);
      return;
    }
  }

}

bool CPhysicsEngine::CheckStaticCollision(CCollider* _collider) const
{
  for (CRigidBodyComponent* iterator : m_staticBodies)
  {
    if (_collider->Collides(*iterator->GetCollider()))
      return true;
  }
  return false;
}
