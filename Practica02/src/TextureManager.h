#pragma once

#include <map>
#include <string>
#include "SingletonBase.h"
#include "litegfx.h"


class CTextureManager : public ISingletonBase<CTextureManager>
{
  DECLARE_SINGLETON_CLASS(CTextureManager);

private:

  typedef std::pair<std::string, ltex_t*>                 TextureRegisterItem;
  typedef std::map<std::string, ltex_t*>                  TextureRegister;
  typedef std::map<std::string, ltex_t*>::iterator        TextureRegisterIterator;
  typedef std::map<std::string, ltex_t*>::const_iterator  TextureRegisterConstIterator;

private:

  TextureRegister m_textureRegister;

public:

  static CTextureManager& GetInstance();
  ~CTextureManager();

  static void Init();
  static void Shutdown();

  const ltex_t* CreateTexture(const char * _sFilename);
  const ltex_t* GetTexture(const char* _sFilename) const;
  void RemoveTexture(const char* _sFilename);

private:

  static ltex_t* CreateTexture_Internal(const char* _sFilename);
  void Clear();


};