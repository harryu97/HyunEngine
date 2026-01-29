#include "Engine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <chrono>
#include <iostream>
#include "Application.h"
#include "audio/AudioManager.h"
#include "physics/PhysicsManager.h"
#include "render/RenderQueue.h"
namespace eng {
void keyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods) {
  auto& inputManager = eng::Engine::getInstance().getInputManager();
  if (action == GLFW_PRESS) {
    std::cout << "IN callback" << std::endl;
    inputManager.SetKeyPressed(key, true);

  } else if (action == GLFW_RELEASE) {
    inputManager.SetKeyPressed(key, false);
  }
}
void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) {
  auto& inputManager = eng::Engine::getInstance().getInputManager();
  if (action == GLFW_PRESS) {
    inputManager.SetMouseButtonPressed(button, true);
  } else if (action == GLFW_RELEASE) {
    inputManager.SetMouseButtonPressed(button, false);
  }
}
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
  auto& inputManager = eng::Engine::getInstance().getInputManager();
  inputManager.SetMousePositionOld(inputManager.GetMousePositioncurrent());
  glm::vec2 currentPos(static_cast<float>(xpos), static_cast<float>(ypos));
  inputManager.SetMousePositionCurrent(currentPos);

  inputManager.SetMousePositionChanged(true);
}
Engine& Engine::getInstance() {
  static Engine instance;
  return instance;
}

bool Engine::Init(int width, int height) {
  if (!m_Application) {
    return false;
  }
  // App register its own types
  Scene::RegisterTypes();
  m_Application->RegisterTypes();
  if (!glfwInit()) {
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(width, height, "GAMEDEV", nullptr, nullptr);
  if (m_window == nullptr) {
    std::cout << "ERROR CREATING WINDOW" << std::endl;
    glfwTerminate();
    return false;
  }
  // Input Callback
  glfwSetKeyCallback(m_window, keyCallback);
  // Mouse Callback
  glfwSetMouseButtonCallback(m_window, mouseButtonCallBack);
  glfwSetCursorPosCallback(m_window, cursorPositionCallback);
  glfwMakeContextCurrent(m_window);
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  if (glfwGetCurrentContext() == nullptr) {
    std::cerr << "ERROR: No current OpenGL context!" << std::endl;

    glfwTerminate();

    return false;
  }

  glewExperimental = GL_TRUE;

  // Initialize glew library

  GLenum glewError = glewInit();

  if (glewError != GLEW_OK) {
    std::cerr << "ERROR GLEWINIT: " << glewGetErrorString(glewError)

              << std::endl;

    std::cerr << "Error code: " << glewError << std::endl;

    glfwTerminate();

    return false;
  }

  m_graphicsAPI.Init();
  m_physicsManager.Init();
  m_audioManager.Init();
  return m_Application->Init();
}
void Engine::Run() {
  if (!m_Application) {
    std::cout << "No Application" << std::endl;
    return;
  }
  m_lastTimePoint = std::chrono::steady_clock::now();
  while (!glfwWindowShouldClose(m_window) &&
         !m_Application->NeedsTobeClosed()) {
    glfwPollEvents();

    auto now = std::chrono::steady_clock::now();
    float deltaTime =
        std::chrono::duration<float>(now - m_lastTimePoint).count();
    m_lastTimePoint = now;

    m_physicsManager.Update(deltaTime);

    m_Application->Update(deltaTime);
    m_graphicsAPI.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_graphicsAPI.ClearBuffers();
    CameraData cameraData;
    std::vector<LightData> lights;
    // For aspect
    int width = 0;
    int height = 0;
    glfwGetWindowSize(m_window, &width, &height);
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    if (m_currentScene) {
      if (auto cameraObject = m_currentScene->getCamera()) {
        // logic for matrices.
        auto cameraComponent = cameraObject->GetComponent<CameraComponent>();
        if (cameraComponent) {
          cameraData.viewMatrix = cameraComponent->GetViewMatrix();
          cameraData.projectionMatrix =
              cameraComponent->GetProjectionMatrix(aspect);
          cameraData.position = cameraObject->GetWorldPosition();
        }
      }
      lights = m_currentScene->CollectLights();
    }
    m_renderQueue.Draw(m_graphicsAPI, cameraData, lights);
    glfwSwapBuffers(m_window);
    // each frame update old pos to current ;
    m_inputManager.SetMousePositionOld(
        m_inputManager.GetMousePositioncurrent());
    m_inputManager.SetMousePositionChanged(false);
  }
}
void Engine::Destroy() {
  if (m_Application) {
    m_Application->Destroy();
    delete m_Application;
    glfwTerminate();
    m_window = nullptr;
  }
  delete m_currentScene;
}

void Engine::SetApplication(Application* app) {
  std::cout << "INSIDE ENGINE SET APPLICATION" << std::endl;
  if (m_Application) {
    std::cout << "ALREADY EXITS" << std::endl;
    m_Application->Destroy();
    delete m_Application;
  }
  m_Application = app;
}
Application* Engine::getApplication() {
  return m_Application;
}
InputManager& Engine::getInputManager() {
  return m_inputManager;
}
GraphicsAPI& Engine::getGraphicsAPI() {
  return m_graphicsAPI;
}

RenderQueue& Engine::getRenderQueue() {
  return m_renderQueue;
}

void Engine::setScene(Scene* scene) {
  m_currentScene = scene;
}

Scene* Engine::getScene() {
  return m_currentScene;
}
FileSystem& Engine::getFileSystem() {
  return m_fileSystem;
}

TextureManager& Engine::getTextureManager() {
  return m_textureManager;
}
PhysicsManager& Engine::getPhysicsManager() {
  return m_physicsManager;
}
AudioManager& Engine::getAudioManager() {
  return m_audioManager;
}

}  // namespace eng
