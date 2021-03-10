#include "RenderEngine.h"
#include "MacroUtility.h"

#include "glfw3.h"
#include "litegfx.h"

// --------------------------------------------------------

constexpr int SCR_WIDTH = 800;
constexpr int SCR_HEIGHT = 600;

// --------------------------------------------------------

CRenderEngine::~CRenderEngine() {}

CRenderEngine& CRenderEngine::GetInstance()
{
  return GetSingletonInstance();
}

void CRenderEngine::SetWindowSizeCallback(GLFWwindow* _pWindow, int _iWidth, int _iHeight)
{
  int iX, iY;
  glfwGetWindowPos(_pWindow, &iX, &iY);
  lgfx_setviewport(iX, iY, _iWidth, _iHeight);
}

void CRenderEngine::Init_Internal()
{
  // Init window
  int iRenderStatus = glfwInit();
  ensure_msg(iRenderStatus == GLFW_TRUE, "GLFW library initialization failed.");
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 02 - Doppler", nullptr, nullptr);
  ensure(window != nullptr);
  glfwMakeContextCurrent(window);
  m_window = window;

  // Init litegfx
  lgfx_setup2d(SCR_WIDTH, SCR_HEIGHT);

  // Bind callbacks related with window
  glfwSetWindowSizeCallback(m_window, &CRenderEngine::SetWindowSizeCallback);

  // Init vars
  m_screenSize = Vec2(SCR_WIDTH, SCR_HEIGHT);
  print_log("Render initialized successfuly.");
}

void CRenderEngine::Init()
{
  CreateSingleton();
  GetSingletonInstance().Init_Internal();
}

void CRenderEngine::Update()
{
  // Clear hidden buffer
  lgfx_clearcolorbuffer(0.1f, 0.1f, 0.1f);

  // Draw with external calls
  m_externalDrawDispatcher.Broadcast(m_screenSize);

  // Swap buffers
  glfwSwapBuffers(m_window);
}

void CRenderEngine::Shutdown()
{
  GetSingletonInstance().Shutdown_Internal();
  DestroySingleton();
}

void CRenderEngine::Shutdown_Internal()
{
  glfwTerminate();
  print_log("Render terminated successfuly.");
}

bool CRenderEngine::IsRunning() const
{
  return glfwWindowShouldClose(m_window) != GLFW_TRUE;
}

void CRenderEngine::CloseWindow()
{
  glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

Vec2 CRenderEngine::GetCursorPosition() const
{
  double dX, dY;
  glfwGetCursorPos(m_window, &dX, &dY);
  return Vec2(static_cast<float>(dX), static_cast<float>(dY));
}

Vec2 CRenderEngine::GetWindowSize() const
{
  int iX, iY;
  glfwGetWindowSize(m_window, &iX, &iY);
  return Vec2(static_cast<float>(iX), static_cast<float>(iY));
}

GLFWwindow* CRenderEngine::GetWindow() const
{
  return m_window;
}

void CRenderEngine::SetClearColor(float _fR, float _fG, float _fB)
{
  //m_backgroundColor.R = _fR;
  //m_backgroundColor.G = _fG;
  //m_backgroundColor.B = _fB;
}

void CRenderEngine::SetBlend(lblend_t _blendMode)
{
  lgfx_setblend(_blendMode);
}

void CRenderEngine::SetColor(float _r, float _g, float _b, float _a)
{
  lgfx_setcolor(_r, _g, _b, _a);
}

void CRenderEngine::RenderImage(const SImageRenderData& _imageData)
{
  ltex_drawrotsized(_imageData.m_tex, _imageData.m_position.GetX(), _imageData.m_position.GetY(),
    _imageData.m_rotation, _imageData.m_pivot.GetX(), _imageData.m_pivot.GetY(), 
    _imageData.m_size.GetX(), _imageData.m_size.GetY(), 
    _imageData.m_uv[0].GetX(), _imageData.m_uv[0].GetY(), _imageData.m_uv[1].GetX(), _imageData.m_uv[1].GetY()
  );
}

stbi_uc* CRenderEngine::LoadBuffer(const char* _filename, int& width_, int& height_)
{
  return stbi_load(_filename, &width_, &height_, nullptr, 4);
}

ltex_t* CRenderEngine::AllocTexture(int _width, int _height)
{
  return ltex_alloc(_width, _height, 0);
}

void CRenderEngine::FillTexture(ltex_t* _texture, stbi_uc* _buffer)
{
  ltex_setpixels(_texture, _buffer);
}

void CRenderEngine::FreeTexture(ltex_t* _texture)
{
  ltex_free(_texture);
}

void CRenderEngine::FreeBuffer(stbi_uc* _buffer)
{
  stbi_image_free(_buffer);
}

void CRenderEngine::SetCameraPosition(const Vec2& _position)
{
  lgfx_setorigin(_position.GetX(), _position.GetY());
}

