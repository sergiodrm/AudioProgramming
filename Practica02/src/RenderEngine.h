#pragma once

#include "SingletonBase.h"
#include "Dispatcher.h"
#include "litegfx.h"
#include "stb_image.h"
#include "Vec2.h"

struct GLFWwindow;

class CRenderEngine : ISingletonBase<CRenderEngine>
{
  DECLARE_SINGLETON_CLASS(CRenderEngine);

  
public:

  struct SImageRenderData
  {
    const ltex_t* m_tex;
    Vec2 m_position;
    float m_rotation;
    Vec2 m_pivot;
    Vec2 m_size;
    Vec2 m_uv[2];
  };

public:

  ~CRenderEngine();
  static CRenderEngine& GetInstance();

  static void Init();
  void Update();
  static void Shutdown();
  bool IsRunning() const;
  void CloseWindow();

  Vec2 GetCursorPosition() const;
  Vec2 GetWindowSize() const;
  GLFWwindow* GetWindow() const;
  void SetClearColor(float _fR, float _fG, float _fB);

  template <typename T, void(T::*M)(const Vec2&)>
  void BindDrawCallback(void* _pInstance);

  template <typename T, void(T::*M)(const Vec2&) const>
  void BindDrawCallback(void* _pInstance);

  /**
   *    litegfx API
   */
  static void SetBlend(lblend_t _blendMode);
  static void SetColor(float _r, float _g, float _b, float _a);
  static void RenderImage(const SImageRenderData& _imageData);
  static stbi_uc* LoadBuffer(const char* _filename, int& width_, int& height_);
  static ltex_t* AllocTexture(int _width, int _height);
  static void FillTexture(ltex_t* _texture, stbi_uc* _buffer);
  static void FreeTexture(ltex_t* _texture);
  static void FreeBuffer(stbi_uc* _buffer);
  static void SetCameraPosition(const Vec2& _position);

  /**
  *   Callbacks
  */
  static void SetWindowSizeCallback(GLFWwindow* _pWindow, int _iWidth, int _iHeight);

private:
  void Init_Internal();
  void Shutdown_Internal();

private:

  Dispatcher<const Vec2&> m_externalDrawDispatcher;
  GLFWwindow* m_window;
  
  Vec2 m_screenSize;


};


/**
 * Templates definition
 */

template <typename T, void(T::* M)(const Vec2&)>
void CRenderEngine::BindDrawCallback(void* _pInstance)
{
  m_externalDrawDispatcher.Bind<T, M>(_pInstance);
}

template <typename T, void(T::*M)(const Vec2&) const>
  void CRenderEngine::BindDrawCallback(void* _pInstance)
{
  m_externalDrawDispatcher.Bind<T, M>(_pInstance);
}

