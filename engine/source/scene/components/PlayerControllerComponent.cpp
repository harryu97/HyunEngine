
#include "PlayerControllerComponent.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/geometric.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
namespace eng {
void PlayerControllerComponent::Update(float deltaTime) {
  auto& inputManager = Engine::getInstance().getInputManager();
  auto rotation = m_owner->GetRotation();
  if (inputManager.IsMousePositionChanged()) {
    const auto& oldPos = inputManager.GetMousePositionOld();
    const auto& current = inputManager.GetMousePositioncurrent();

    // how much moved
    float deltaX = current.x - oldPos.x;
    float deltaY = current.y - oldPos.y;
    // rot around y
    float yDeltaAngle = -deltaX * m_sensitivity * deltaTime;
    m_yRot += yDeltaAngle;
    glm::quat yRot =
        glm::angleAxis(glm::radians(m_yRot), glm::vec3(0.0f, 1.0f, 0.0f));
    // rot around x
    float xDeltaAngle = -deltaY * m_sensitivity * deltaTime;
    m_xRot += xDeltaAngle;
    m_xRot = std::clamp(m_xRot, -89.0f, 89.0f);
    glm::quat xRot =
        glm::angleAxis(glm::radians(m_xRot), glm::vec3(1.0f, 0.0f, 0.0f));

    // rotation=deltaX* sensitivity*deltaTime;
    // rot around y axis;
    // float yAngle = -deltaX * 0.008f;
    // glm::quat yRot = glm::angleAxis(yAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    //    rotation.y -= deltaX * m_sensitivity * deltaTime;
    // rot around x axis -pitch
    // float xAngle = -deltaY * 0.008f;
    // glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
    // glm::quat xRot = glm::angleAxis(xAngle, right);
    // rotation.x -= deltaY * m_sensitivity * deltaTime;

    // for combining just multiply
    // glm::quat deltaRot = yRot * xRot;
    // rotation = glm::normalize(deltaRot * rotation);
    rotation = glm::normalize(yRot * xRot);

    m_owner->SetRotation(rotation);
  }
  // move relative to camera rotation first
  // forward vector
  glm::vec3 front = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);

  glm::vec3 move(0.0f);
  // auto position = m_owner->GetPosition();
  //  Left Right movement
  auto& input = eng::Engine::getInstance().getInputManager();
  if (input.IsKeyPressed(GLFW_KEY_A)) {
    // position -= right * m_moveSpeed * deltaTime;
    move -= right;
  } else if (input.IsKeyPressed(GLFW_KEY_D)) {
    // position += right * m_moveSpeed * deltaTime;
    move += right;
  }
  if (input.IsKeyPressed(GLFW_KEY_W)) {
    // position += front * m_moveSpeed * deltaTime;
    move += front;
  } else if (input.IsKeyPressed(GLFW_KEY_S)) {
    //   position -= front * m_moveSpeed * deltaTime;
    move -= front;
  }
  if (inputManager.IsKeyPressed(GLFW_KEY_SPACE)) {
    m_kinematicController->Jump(glm::vec3(0.0f, 5.0f, 0.0f));
  }
  // if there is movement
  if (glm::dot(move, move) > 0) {
    move = glm::normalize(move);
  }

  m_kinematicController->Walk(move * m_moveSpeed * deltaTime);
  m_owner->SetPosition(m_kinematicController->GetPosition());

  // m_owner->SetPosition(position);
}

void PlayerControllerComponent::Init() {
  m_kinematicController = std::make_unique<KinematicCharacterController>(
      0.4f, 1.2f, m_owner->GetWorldPosition());
}
bool PlayerControllerComponent::OnGround() const {
  if (m_kinematicController) {
    return m_kinematicController->OnGround();
  }
  return false;
}
}  // namespace eng
