#pragma once
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
namespace eng {
class KinematicCharacterController {
  // Will be a capsule collider
 public:
  KinematicCharacterController(float radius,
                               float height,
                               const glm::vec3& position);
  ~KinematicCharacterController();
  glm::vec3 GetPosition() const;
  glm::quat GetRotation() const;

  void Walk(const glm::vec3& direction);
  void Jump(const glm::vec3& direction);
  bool OnGround() const;

 private:
  float m_height = 1.2f;
  float m_radius = 0.4f;
  std::unique_ptr<btPairCachingGhostObject> m_ghost;
  std::unique_ptr<btKinematicCharacterController> m_controller;
};
}  // namespace eng
