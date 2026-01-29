#pragma once
#include <chrono>
#include <memory>
#include "Application.h"
#include "audio/AudioManager.h"
#include "graphics/GraphicsAPI.h"
#include "graphics/Texture.h"
#include "input/InputManager.h"
#include "io/FileSystem.h"
#include "physics/PhysicsManager.h"
#include "render/RenderQueue.h"
#include "scene/Component.h"
#include "scene/GameObject.h"
#include "scene/Scene.h"
#include "scene/components/CameraComponent.h"
struct GLFWwindow;
namespace eng {

class Application;
class Engine {
 public:
  static Engine& getInstance();

 private:
  Engine() = default;
  Engine(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine& operator=(const Engine&) = delete;
  Engine& operator=(Engine&) = delete;

 public:
  bool Init(int width, int height);
  void Run();
  void Destroy();

  void SetApplication(Application* app);
  Application* getApplication();
  InputManager& getInputManager();
  GraphicsAPI& getGraphicsAPI();
  RenderQueue& getRenderQueue();
  FileSystem& getFileSystem();
  TextureManager& getTextureManager();
  void setScene(Scene* scene);
  Scene* getScene();
  PhysicsManager& getPhysicsManager();
  AudioManager& getAudioManager();

 private:
  Application* m_Application = nullptr;
  std::chrono::steady_clock::time_point m_lastTimePoint;
  GLFWwindow* m_window = nullptr;
  InputManager m_inputManager;
  GraphicsAPI m_graphicsAPI;
  RenderQueue m_renderQueue;
  TextureManager m_textureManager;
  Scene* m_currentScene;
  FileSystem m_fileSystem;
  PhysicsManager m_physicsManager;
  AudioManager m_audioManager;
};

}  // namespace eng
