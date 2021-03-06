#pragma once

#include "SingletonBase.h"
#include <vector>

#include "Vec2.h"

class CCollider;
class CRigidBodyComponent;

class CPhysicsEngine : public ISingletonBase<CPhysicsEngine>
{
  DECLARE_SINGLETON_CLASS(CPhysicsEngine);
public:

  static void Init();
  static CPhysicsEngine& GetInstance();
  static void Shutdown();

  void Update(float _deltaTime);
  
  float GetGravity() const;
  void SetGravity(float _gravity);

  void AddDynamicRigidBody(CRigidBodyComponent* _rigidBody);
  void AddStaticRigidBody(CRigidBodyComponent* _rigidBody);
  void EraseRigidBody(CRigidBodyComponent* _rigidBody);

  bool CheckStaticCollision(CCollider* _collider) const;

private:

  std::vector<CRigidBodyComponent*> m_staticBodies;
  std::vector<std::pair<float, CRigidBodyComponent*>> m_dynamicBodies;
  float m_gravity;
  
};

/**
 * INLINES
 */

inline float CPhysicsEngine::GetGravity() const             { return m_gravity; }
inline void CPhysicsEngine::SetGravity(float _gravity)      { m_gravity = _gravity; }

