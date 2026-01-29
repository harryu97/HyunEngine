#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
// This files stores usable data
namespace eng {
struct CameraData {
  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;
  glm::vec3 position;
};
struct LightData {
  glm::vec3 color;
  glm::vec3 position;
};
}  // namespace eng
