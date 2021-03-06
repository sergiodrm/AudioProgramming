#include "TextureManager.h"
#include "MacroUtility.h"
#include "RenderEngine.h"
#include "stb_image.h"

CTextureManager& CTextureManager::GetInstance()
{
  return GetSingletonInstance();
}

CTextureManager::~CTextureManager()
{
  Clear();
}

void CTextureManager::Init()
{
  CreateSingleton();
}

void CTextureManager::Shutdown()
{
  GetSingletonInstance().Clear();
  DestroySingleton();
}

const ltex_t* CTextureManager::CreateTexture(const char * _sFilename)
{
  ensure(_sFilename != nullptr);
  const ltex_t* texture = GetTexture(_sFilename);
  if (texture == nullptr)
  {
    PRINT_LOG("Loading new texture: \"%s\"", _sFilename);
    ltex_t* newTexture = CreateTexture_Internal(_sFilename);
    m_textureRegister.insert(TextureRegisterItem(_sFilename, newTexture));
    return newTexture;
  }
  else
  {
    return texture;
  }
}

const ltex_t* CTextureManager::GetTexture(const char* _sFilename) const
{
  TextureRegisterConstIterator iterator = m_textureRegister.find(_sFilename);
  if (iterator != m_textureRegister.end())
  {
    return iterator->second;
  }
  return nullptr;
}

void CTextureManager::RemoveTexture(const char* _sFilename)
{
  TextureRegisterIterator iterator = m_textureRegister.find(_sFilename);
  if (iterator != m_textureRegister.end())
  {
    PRINT_LOG("Removing texture from memory: \"%s\"", _sFilename);
    ltex_free(iterator->second);
    m_textureRegister.erase(iterator);
  }
}

ltex_t* CTextureManager::CreateTexture_Internal(const char* _sFilename)
{
  // Load buffer.
  int width, height;
  stbi_uc* buffer = CRenderEngine::LoadBuffer(_sFilename, width, height);
  ensure(buffer != nullptr);

  // Alloc openGL texture.
  ltex_t* texture = CRenderEngine::AllocTexture(width, height);
  CRenderEngine::FillTexture(texture, buffer);
  ensure(texture != nullptr);

  // Free useless buffer.
  CRenderEngine::FreeBuffer(buffer);

  return texture;
}

void CTextureManager::Clear()
{
  for (std::pair<const std::string, ltex_t*>& iterator : m_textureRegister)
  {
    ensure(iterator.second != nullptr);
    PRINT_LOG("Removing texture from memory: \"%s\"", iterator.first.c_str());
    CRenderEngine::FreeTexture(iterator.second);
  }
  m_textureRegister.clear();
}
