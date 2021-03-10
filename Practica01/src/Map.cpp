#include "Map.h"
#include "TextureManager.h"
#include "MacroUtility.h"
#include "Collider.h"
#include "GameObject.h"
#include "PhysicsEngine.h"
#include "pugixml.hpp"
#include "RenderEngine.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "Utility.h"

CMap::CMap()
  : m_textureColumns(0), 
  m_mapWidthInTiles(0), m_mapHeightInTiles(0),
  m_tileWidth(0), m_tileHeight(0),
  m_firstgid(0), m_mapTexture(nullptr)
{}

Vec2 CMap::GetSize() const
{
  Vec2 size(static_cast<float>(m_tileWidth * m_mapWidthInTiles), static_cast<float>(m_tileHeight * m_mapHeightInTiles));
  return size;
}

void CMap::Draw()
{
  ensure_msg(m_mapTexture != nullptr, "Texture must be loaded before call draw method.");
  // Get delta uvs inside texture
  float deltaWidthUV = static_cast<float>(m_tileWidth) / static_cast<float>(m_mapTexture->width);
  float deltaHeightUV = static_cast<float>(m_tileHeight) / static_cast<float>(m_mapTexture->height);

  // Init image data to render engine
  CRenderEngine::SImageRenderData imageRenderData;
  imageRenderData.m_tex = m_mapTexture;
  imageRenderData.m_pivot = Vec2();
  imageRenderData.m_rotation = 0.f;
  imageRenderData.m_size.SetX(static_cast<float>(m_tileWidth));
  imageRenderData.m_size.SetY(static_cast<float>(m_tileHeight));

  // Set render engine to draw tile
  CRenderEngine::SetBlend(BLEND_ALPHA);
  CRenderEngine::SetColor(1.f, 1.f, 1.f, 1.f);
  for (size_t row = 0; row < m_mapHeightInTiles; ++row)
  {
    for (size_t col = 0; col < m_mapWidthInTiles; ++col)
    {
      size_t dataIndex = m_mapWidthInTiles * row + col;
      size_t gid = m_gid[dataIndex];

      if (gid != 0)
      {
        // Get uvs from gid
        size_t textureRow = (gid - m_firstgid) / m_textureColumns;
        size_t textureCol = (gid - m_firstgid) % m_textureColumns;
        float u0 = static_cast<float>(textureCol) * deltaWidthUV;
        float v0 = static_cast<float>(textureRow) * deltaHeightUV;
        float u1 = u0 + deltaWidthUV;
        float v1 = v0 + deltaHeightUV;
        imageRenderData.m_position = Vec2(static_cast<float>(col * m_tileWidth), static_cast<float>(row * m_tileHeight));
        imageRenderData.m_uv[0] = Vec2(u0, v0);
        imageRenderData.m_uv[1] = Vec2(u1, v1);

        // Render
        CRenderEngine::RenderImage(imageRenderData);
      }
    }
  }
}

void CMap::GenerateCollidersMap() const
{
  for (size_t index = 0; index < m_gid.size(); ++index)
  {
    if (IsCollideable(index))
    {
      size_t row = index / m_mapWidthInTiles;
      size_t col = index % m_mapWidthInTiles;
      Vec2 colliderPosition(static_cast<float>(col * m_tileWidth), static_cast<float>(row * m_tileHeight));
      CGameObject* wallObject = CGameObject::Create();
      CRigidBodyComponent* rigidBodyComponent = wallObject->AddComponent<CRigidBodyComponent>();
      rigidBodyComponent->CreateCollider(
        CRigidBodyComponent::Rect, 
        CRigidBodyComponent::Static, 
        colliderPosition, 
        Vec2(static_cast<float>(m_tileWidth), static_cast<float>(m_tileHeight))
      );
      rigidBodyComponent->DeactivePhysics();
      CPhysicsEngine::GetInstance().AddStaticRigidBody(rigidBodyComponent);
      wallObject->GetComponent<CTransformComponent>()->SetPosition(colliderPosition);
      wallObject->Active();
    }
  }
}

CMap* CMap::LoadMap(const char* _filename, uint16_t _firstColId)
{
  ensure(_filename != nullptr);

  CMap* newMap = new CMap();

  pugi::xml_document doc;
  pugi::xml_parse_result loadResult = doc.load_file(_filename);
  if (!loadResult)
  {
    print_error(loadResult.description());
    return nullptr;
  }
  pugi::xml_node mapNode = doc.child("map");
  newMap->m_mapWidthInTiles = mapNode.attribute("width").as_int();
  newMap->m_mapHeightInTiles = mapNode.attribute("height").as_int();
  newMap->m_tileWidth = mapNode.attribute("tilewidth").as_int();
  newMap->m_tileHeight = mapNode.attribute("tileheight").as_int();

  pugi::xml_node tilesetNode = mapNode.child("tileset");
  newMap->m_firstgid = tilesetNode.attribute("firstgid").as_int();
  newMap->m_textureColumns = tilesetNode.attribute("columns").as_int();

  pugi::xml_node imageNode = tilesetNode.child("image");
  //int iImageWidth = imageNode.attribute("width").as_int();
  //int iImageHeight = imageNode.attribute("height").as_int();
  std::string sMapImageSource = imageNode.attribute("source").as_string();
  newMap->m_mapTexture = CTextureManager::GetInstance().CreateTexture((Utility::ExtractPath(_filename) + sMapImageSource).c_str());
  
  pugi::xml_node tileNode = mapNode.child("layer").child("data").child("tile");
  for (pugi::xml_node tileNode = mapNode.child("layer").child("data").child("tile"); tileNode; tileNode = tileNode.next_sibling("tile"))
  {
    newMap->m_gid.push_back(tileNode.attribute("gid").as_uint());
  }

  newMap->GenerateCollidersMap();
  return newMap;
}

bool CMap::IsCollideable(size_t _index) const
{
  if (m_gid[_index] != 0)
  {
    auto I2RC = [&](size_t _index, size_t& row_, size_t& col_)
    {
      row_ = _index / m_mapWidthInTiles;
      col_ = _index % m_mapWidthInTiles;
    };
    auto RC2I = [&](size_t _row, size_t _col) -> size_t
    {
      return (_row * m_mapWidthInTiles) + _col;
    };

    size_t row, col;
    I2RC(_index, row, col);
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; ++i)
    {
      size_t rowToCheck = row + directions[i][0];
      size_t colToCheck = col + directions[i][1];
      if (rowToCheck < m_mapHeightInTiles && colToCheck < m_mapWidthInTiles)
      {
        size_t indexToCheck = RC2I(static_cast<size_t>(rowToCheck), static_cast<size_t>(colToCheck));
          if (m_gid[indexToCheck] == 0)
            return true;
      }
    }
  }
  return false;
}
