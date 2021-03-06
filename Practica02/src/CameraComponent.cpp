#include "CameraComponent.h"


#include "GameObject.h"
#include "RenderEngine.h"
#include "TransformComponent.h"
#include "World.h"


CCameraComponent::CCameraComponent()
  : m_bCameraActive(false)
{}

void CCameraComponent::Update(float _deltaTime)
{
  if (IsActive() && IsCameraActive())
  {
    Vec2 screenSize = CRenderEngine::GetInstance().GetWindowSize();
    Vec2 playerPosition = GetOwner()->GetComponent<CTransformComponent>()->GetPosition();
    Vec2 cameraPosition = Vec2(playerPosition.GetX() - screenSize.GetX() / 2.f, playerPosition.GetY() - screenSize.GetY() / 2.f);
    Vec2 mapSize = CWorld::GetInstance().GetMap()->GetSize();

    cameraPosition.SetX(Math::Clamp<float>(cameraPosition.GetX(), 0.f, mapSize.GetX() - screenSize.GetX()));
    cameraPosition.SetY(Math::Clamp<float>(cameraPosition.GetY(), 0.f, mapSize.GetY() - screenSize.GetY()));
    CRenderEngine::SetCameraPosition(cameraPosition);
  }
}

