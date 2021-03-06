#pragma once

#include <vector>
#include "litegfx.h"
#include "Vec2.h"

class CMap
{

public:

  static CMap* LoadMap(const char* _filename, uint16_t _firstColId);

  Vec2 GetSize() const;
  void Draw();
  void GenerateCollidersMap() const;
  
private:

  CMap();
  bool IsCollideable(size_t _index) const;

  size_t m_textureColumns;
  size_t m_mapWidthInTiles;
  size_t m_mapHeightInTiles;
  size_t m_tileWidth;
  size_t m_tileHeight;
  size_t m_firstgid;
  std::vector<size_t> m_gid;
  const ltex_t* m_mapTexture;
};

