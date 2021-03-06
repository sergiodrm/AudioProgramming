
#include "InputManager.h"
#include "glfw3.h"
#include "RenderEngine.h"

void CInputManager::Init()
{
  CreateSingleton();
  GetSingletonInstance().Init_Internal();
}

CInputManager& CInputManager::GetInstance()
{
  return GetSingletonInstance();
}

void CInputManager::Shutdown()
{
  GetInstance().Shutdown_Internal();
  DestroySingleton();
}

void CInputManager::Update()
{
  glfwPollEvents();
}

void CInputManager::KeyboardCallback(GLFWwindow* _pWindow, int _button, int, int _action, int)
{
  SInputCode::EKey keyCode = SInputCode::GetKeyCode(_button);
  SInputCode::EAction actionCode = SInputCode::GetActionCode(_action);
  GetInstance().m_keyboardCallbacks.Broadcast(keyCode, actionCode);
}

void CInputManager::MouseButtonCallback(GLFWwindow* _pWindow, int _button, int _action, int _mode)
{
  GetInstance().m_mouseButtonCallbacks.Broadcast(_button, _action);
}

void CInputManager::Init_Internal()
{
  glfwSetMouseButtonCallback(CRenderEngine::GetInstance().GetWindow(), &CInputManager::MouseButtonCallback);
  glfwSetKeyCallback(CRenderEngine::GetInstance().GetWindow(), &CInputManager::KeyboardCallback);
}

void CInputManager::Shutdown_Internal()
{
  
}

