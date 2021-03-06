#pragma once

#include "Component.h"
#include "Vec2.h"

class CCollider;

class CRigidBodyComponent : public CComponent
{
public:

  enum EColliderType : int
  {
    Rect, Circle, Pixel
  };

  enum EColliderStatus : int
  {
    Static, Dynamic
  };

  CRigidBodyComponent();

  //virtual void OnCreate() override;
  virtual void Update(float _deltaTime) override;
  virtual void OnDestroy() override;

  void CreateCollider(EColliderType _type, EColliderStatus _status, const Vec2& _position, const Vec2& _size);
  void DestroyCollider();

  CCollider* GetCollider() const;
  bool CheckCollision(const CCollider& _collider) const;
  bool CheckAvailablePosition(const Vec2& _position);

  void ActivePhysics();
  void DeactivePhysics();
  bool IsPhysicsActived() const;

  void AddVelocityImpulse(const Vec2& _impulse);
  bool OnFloor();

private:

  CCollider* m_collider;
  bool m_bSimulatePhysics;
  Vec2 m_velocityImpulse;

};


inline void CRigidBodyComponent::ActivePhysics()          { m_bSimulatePhysics = true; }
inline void CRigidBodyComponent::DeactivePhysics()        { m_bSimulatePhysics = false; }
inline bool CRigidBodyComponent::IsPhysicsActived() const { return m_bSimulatePhysics; }
