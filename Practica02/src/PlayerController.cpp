#include "PlayerController.h"
#include "InputManager.h"
#include "World.h"
#include "glfw3.h"

CPlayerController::CPlayerController()
  : m_pControlledSprite(nullptr), m_bInMovement(false) {}

void CPlayerController::Update(float _deltaTime)
{
  if (m_bInMovement)
  {
    
  }
}

void CPlayerController::ProcessInputPlayer(bool _bProcess)
{
  if (_bProcess)
  {
    CInputManager::GetInstance().BindKeyboardCallback<CPlayerController, &CPlayerController::ReceiveInput>(this);
  }
}

void CPlayerController::AddControlledSprite(CSprite& _sprite)
{
  m_pControlledSprite = &_sprite;
}

void CPlayerController::ReceiveInput(int _button, int _action)
{
  float delta = _action == GLFW_PRESS ? 1.f : 0.f;
  switch (_button)
  {
  case GLFW_KEY_A:
    m_movementInput.SetX(-delta);
    break;
  case GLFW_KEY_D:
    m_movementInput.SetX(delta);
    break;
  case GLFW_KEY_W:
    m_movementInput.SetY(-delta);
    break;
  case GLFW_KEY_S:
    m_movementInput.SetY(delta);
    break;
  }
}
