#include "InputCodes.h"
#include "glfw3.h"

int SInputCode::GetKeyCode(EKey _key)
{
  switch(_key)
  {
  case EKey::A:       return GLFW_KEY_A;
  case EKey::S:       return GLFW_KEY_S;
  case EKey::D:       return GLFW_KEY_D;
  case EKey::W:       return GLFW_KEY_W;
  case EKey::Up:      return GLFW_KEY_UP;
  case EKey::Down:    return GLFW_KEY_DOWN;
  case EKey::Left:    return GLFW_KEY_LEFT;
  case EKey::Right:   return GLFW_KEY_RIGHT;
  case EKey::Escape:  return GLFW_KEY_ESCAPE;
  case EKey::Space:   return GLFW_KEY_SPACE;
  default:            return GLFW_FALSE;
  }
}

SInputCode::EKey SInputCode::GetKeyCode(int _key)
{
  switch(_key)
  {
  case GLFW_KEY_A:      return EKey::A;
  case GLFW_KEY_S:      return EKey::S;
  case GLFW_KEY_D:      return EKey::D;
  case GLFW_KEY_W:      return EKey::W;
  case GLFW_KEY_UP:     return EKey::Up;
  case GLFW_KEY_DOWN:   return EKey::Down;
  case GLFW_KEY_LEFT:   return EKey::Left;
  case GLFW_KEY_RIGHT:  return EKey::Right;
  case GLFW_KEY_ESCAPE: return EKey::Escape;
  case GLFW_KEY_SPACE:  return EKey::Space;
  default:              return EKey::InvalidKey;
  }
}
SInputCode::EAction SInputCode::GetActionCode(int _action)
{
  switch (_action)
  {
  case GLFW_PRESS:    return EAction::Press;
  case GLFW_RELEASE:  return EAction::Release;
  case GLFW_REPEAT:   return EAction::Maintain;
  default:            return EAction::InvalidAction;
  }
}

int SInputCode::GetActionCode(EAction _action)
{
  switch(_action)
  {
  case EAction::Press:    return GLFW_PRESS;
  case EAction::Release:  return GLFW_RELEASE;
  case EAction::Maintain: return GLFW_REPEAT;
  default:                return GLFW_FALSE;
  }
}
