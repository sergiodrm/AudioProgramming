#pragma once

#include <vector>

template <typename ...Args>
class Dispatcher
{
public:
  /**
   * Typedef to the function model.
   */
  typedef void(*FunctionPointer)(void*, Args...);
  typedef std::pair<void*, FunctionPointer> Callback;

  Dispatcher() {}

  /**
   * @brief Bind a method of an instance.
   */
  template <typename T, void(T::*M)(Args...)>
  void Bind(void* _pInstance)
  {
    Callback pair = std::make_pair(_pInstance, &Invoke<T, M>);
    m_delegates.push_back(pair);
  }

  /**
   * @brief Bind a const method of an instance.
   */
  template <typename T, void(T::*M)(Args...) const>
  void Bind(void* _pInstance)
  {
    Callback pair = std::make_pair(_pInstance, &Invoke<T, M>);
    m_delegates.push_back(pair);
  }

  /**
   * @brief Call all binded methods with the arguments args.
   */
  void Broadcast(Args... args)
  {
    for (Callback& it : m_delegates)
    {
      (it.second)(it.first, args...);
    }
  }

private:

  /**
   * @brief this method will do the cast to the corresponding class and will call the binded method with the arguments.
   */
  template <typename T, void(T::*M)(Args...)>
  static void Invoke(void* _pInstance, Args... args)
  {
    (static_cast<T*>(_pInstance)->*M)(args...);
  }

  /**
   * @brief The same of the last Invoke method, but with binded const methods of the instance.
   */
  template <typename T, void(T::*M)(Args...) const>
  static void Invoke(void* _pInstance, Args... args)
  {
    (static_cast<T*>(_pInstance)->*M)(args...);
  }

  /**
   * @brief Vector of pairs where the instance and a reference to a "Invoke" method will be saved.
   */
  std::vector<Callback> m_delegates;

};