
#include "CameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include "../GameObject.h"
namespace eng {
void CameraComponent::Update(float deltaTime) {}
glm::mat4 CameraComponent::GetViewMatrix() const {
  // for projection we inverse the matrix
  // Camera has differnet transform order
  glm::mat4 mat = glm::mat4(1.0f);

  mat = glm::mat4_cast(m_owner->GetRotation());

  // Apply translation
  // Does not apply scale here for a view
  //  mat = glm::translate(mat, m_owner->GetPosition());

  // For more realistic
  mat[3] = glm::vec4(m_owner->GetPosition(), 1.0f);

  if (m_owner->getParent()) {
    // if it has parent apply by parent
    mat = m_owner->getParent()->GetWorldTransform() * mat;
  }

  return glm::inverse(mat);
}

glm::mat4 CameraComponent::GetProjectionMatrix(float aspect) const {
  return glm::perspective(glm::radians(m_fov), aspect, m_nearPlane, m_farPlane);
}
}  // namespace eng
//
