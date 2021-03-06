#pragma once

#include "SingletonBase.h"
#include "Dispatcher.h"
#include "InputCodes.h"

struct GLFWwindow;

class CInputManager : public ISingletonBase<CInputManager>
{
  DECLARE_SINGLETON_CLASS(CInputManager);

public:

  /**
   * Singleton methods
   */
  static void Init();
  static CInputManager& GetInstance();
  static void Shutdown();

  /**
   * @brief Method to update status every frame
   */
  void Update();

  /**
   * @brief Bind function to a input from keyboard.
   * example: CInputManager::GetInstance().BindKeyboardCallback<CPlayerController, &CPlayerController::ReceiveInput>(&instance);
   */
  template <typename T, void(T::*M)(SInputCode::EKey, SInputCode::EAction)>
  void BindKeyboardCallback(void* _pInstance);

  /**
   * @brief Bind function to a input from mouse button.
   * example: CInputManager::GetInstance().BindKeyboardCallback<CPlayerController, &CPlayerController::ReceiveInput>(&instance);
   */
  template <typename T, void(T::* M)(int, int)>
  void BindMouseButtonCallback(void* _pInstance);

  /**
   * GLFW callbacks to catch the input
   */
  static void KeyboardCallback(GLFWwindow* _pWindow, int _button, int, int _action, int);
  static void MouseButtonCallback(GLFWwindow* _pWindow, int _button, int _action, int _mode);

private:

  /**
   * Init & Shutdown private methods which will be called from singleton methods.
   */
  void Init_Internal();
  void Shutdown_Internal();

  /**
   * Dispatcher to bind callbacks from diferent input.
   */
  Dispatcher<SInputCode::EKey, SInputCode::EAction> m_keyboardCallbacks;
  Dispatcher<int, int> m_mouseButtonCallbacks;

};

/**
 * Template definitions
 */

template <typename T, void(T::* M)(SInputCode::EKey, SInputCode::EAction)>
void CInputManager::BindKeyboardCallback(void* _pInstance)
{
  m_keyboardCallbacks.Bind<T, M>(_pInstance);
}

template <typename T, void(T::* M)(int, int)>
void CInputManager::BindMouseButtonCallback(void* _pInstance)
{
  m_mouseButtonCallbacks.Bind <T, M>(_pInstance);
}
