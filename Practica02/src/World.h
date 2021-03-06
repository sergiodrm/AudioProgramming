#pragma once

#include <vector>
#include "SingletonBase.h"
#include "Vec2.h"
#include "Map.h"


class CGameObject;

class CWorld : public ISingletonBase<CWorld>
{
  DECLARE_SINGLETON_CLASS(CWorld);
public:

  static void Init();
  static CWorld& GetInstance();
  static void Shutdown();
  
  void Update(float _deltaTime);
  void RenderWorld(const Vec2& _screenSize) const;

  void AddGameObject(CGameObject* _gameObject);
  void RemoveGameObject(CGameObject* _gameObject);

  void AddBackground(CGameObject* _background);
  void RemoveBackground(CGameObject* _background);

  CMap* GetMap() const;
  void SetMap(CMap* _map);

  const Vec2& GetCurrentCameraPosition() const;

private:

  void Clear();

  CMap* m_map;
  std::vector<CGameObject*> m_gameObjects;
  std::vector<CGameObject*> m_backgrounds;

};


inline CMap* CWorld::GetMap() const     { return m_map; }
inline void CWorld::SetMap(CMap* _map)  { m_map = _map; }


