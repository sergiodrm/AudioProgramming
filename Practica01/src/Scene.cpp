#include "Scene.h"


#include "BackgroundComponent.h"
#include "CameraComponent.h"
#include "Collider.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "RenderEngine.h"
#include "RigidBodyComponent.h"

#define BACKGROUND_TEXTURE_FILE   "data/clouds.png"
#define RUN_TEXTURE_FILE          "data/run.png"
#define IDLE_TEXTURE_FILE         "data/idle.png"
#define MAP_TMX_FILE              "data/customMap.tmx"

CScene::CScene() {}

void CScene::Init()
{
  // Create background
  const ltex_t* cloudsBackground = CTextureManager::GetInstance().CreateTexture(BACKGROUND_TEXTURE_FILE);
  CGameObject* backgroundObject = CGameObject::Create();
  CWorld::GetInstance().AddBackground(backgroundObject);
  CWorld::GetInstance().RemoveGameObject(backgroundObject);
  CBackgroundComponent* backgroundComponent = backgroundObject->AddComponent<CBackgroundComponent>();
  backgroundComponent->SetTexture(cloudsBackground, 1, 1);
  backgroundComponent->SetScrollSpeed(Vec2(-5.f, 7.f));
  backgroundObject->Active();

  // Load map
  CWorld::GetInstance().SetMap(CMap::LoadMap(MAP_TMX_FILE, 0));

  // Load sprite textures
  CTextureManager::GetInstance().CreateTexture(RUN_TEXTURE_FILE);
  CTextureManager::GetInstance().CreateTexture(IDLE_TEXTURE_FILE);

  // Create player
  m_playerGameObject = CGameObject::Create();
  CMovementComponent* movementComponent = m_playerGameObject->AddComponent<CMovementComponent>();
  movementComponent->SetControlledByPlayer(true);
  CSpriteComponent* spriteComponent = m_playerGameObject->AddComponent<CSpriteComponent>();
  spriteComponent->SetTexture(CTextureManager::GetInstance().GetTexture(IDLE_TEXTURE_FILE), 1, 1);
  spriteComponent->SetFPS(8);
  CRigidBodyComponent* rigidBodyComponent = m_playerGameObject->AddComponent<CRigidBodyComponent>();
  rigidBodyComponent->CreateCollider(CRigidBodyComponent::Rect, CRigidBodyComponent::Dynamic, Vec2(200.f, 200.f), spriteComponent->GetSize());
  rigidBodyComponent->ActivePhysics();
  CCameraComponent* cameraComponent = m_playerGameObject->AddComponent<CCameraComponent>();
  cameraComponent->ActiveCamera();
  m_playerGameObject->Active();

  // Bind method to receive input from player
  CInputManager::GetInstance().BindKeyboardCallback<CScene, &CScene::ReceiveInputPlayer>(this);
}


void CScene::Shutdown()
{
  CTextureManager::GetInstance().RemoveTexture(BACKGROUND_TEXTURE_FILE);
  CTextureManager::GetInstance().RemoveTexture(IDLE_TEXTURE_FILE);
  CTextureManager::GetInstance().RemoveTexture(RUN_TEXTURE_FILE);
}

void CScene::ReceiveInputPlayer(SInputCode::EKey _key, SInputCode::EAction _action)
{
  const ltex_t* updatedTexture = nullptr;
  int horizontalFrames = 1;
  int verticalFrames = 1;
  CSpriteComponent* spriteComponent = m_playerGameObject->GetComponent<CSpriteComponent>();

  bool moveRight = _key == SInputCode::D || _key == SInputCode::Right;
  bool moveLeft = _key == SInputCode::A || _key == SInputCode::Left;
  if (moveLeft || moveRight)
  {
    if (_action == SInputCode::Release)
    {
      updatedTexture = CTextureManager::GetInstance().GetTexture(IDLE_TEXTURE_FILE);
    }
    else
    {
      updatedTexture = CTextureManager::GetInstance().GetTexture(RUN_TEXTURE_FILE);
      horizontalFrames = 6;
    }
    spriteComponent->SetReflexSprite(moveLeft, false);
    spriteComponent->SetTexture(updatedTexture, horizontalFrames, verticalFrames);
  }
}
