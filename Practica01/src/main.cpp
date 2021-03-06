#pragma warning (disable : 4098)
#include "Scene.h"
#include "RenderEngine.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "PhysicsEngine.h"
#include "TimeManager.h"
#include "AudioManager.h"
#include "CompileLibs.h"


int main() 
{
  // Init tiny engine
  CRenderEngine::Init();
  CTextureManager::Init();
  CAudioManager::Init();
  CInputManager::Init();
  CPhysicsEngine::Init();
  CTimeManager::Init();
  CWorld::Init();

  // Init data
  CScene gameScene;
  gameScene.Init();

  // Game loop
  while (CRenderEngine::GetInstance().IsRunning())
  {
    // Prepare timer to logic update
    CTimeManager::GetTimer().InitToProcess();
    while (CTimeManager::GetTimer().Process())
    {
      // Update input
      CInputManager::GetInstance().Update();
      // Update physics
      CPhysicsEngine::GetInstance().Update(static_cast<float>(CTimeManager::GetTimer().GetFixedTick()));
      // Update logic
      CWorld::GetInstance().Update(static_cast<float>(CTimeManager::GetTimer().GetFixedTick()));
    }
    // Render frame
    CRenderEngine::GetInstance().Update();
  }

  // Shutdown
  gameScene.Shutdown();

  CWorld::Shutdown();
  CTimeManager::Shutdown();
  CPhysicsEngine::Shutdown();
  CInputManager::Shutdown();
  CAudioManager::Shutdown();
  CTextureManager::Shutdown();
  CRenderEngine::Shutdown();

  return 0;
}
