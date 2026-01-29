#include "RenderQueue.h"
#include "../graphics/GraphicsAPI.h"
#include "../graphics/ShaderProgram.h"
#include "../render/Material.h"
#include "../render/Mesh.h"
#include "glm/detail/func_geometric.hpp"
namespace eng {
void RenderQueue::Submit(const RenderCommand& command) {
  m_command.push_back(command);
}

void RenderQueue::Draw(GraphicsAPI& graphicsAPI,
                       const CameraData& cameraData,
                       const std::vector<LightData>& lights) {
  for (auto& command : m_command) {
    graphicsAPI.BindMaterial(command.material);
    auto shaderProgram = command.material->GetShaderProgram();
    shaderProgram->SetUniform("uModel", command.modelMatrix);
    shaderProgram->SetUniform("uView", cameraData.viewMatrix);
    shaderProgram->SetUniform("uProjection", cameraData.projectionMatrix);
    shaderProgram->SetUniform("uCameraPos", cameraData.position);
    if (!lights.empty()) {
      auto& light = lights[0];
      shaderProgram->SetUniform("uLight.color", light.color);
      //  shaderProgram->SetUniform("uLight.position", light.position);
      shaderProgram->SetUniform("uLight.direction",
                                glm::normalize(-light.position));
    }
    graphicsAPI.BindMesh(command.mesh);
    graphicsAPI.DrawMesh(command.mesh);
    graphicsAPI.UnbindMesh(command.mesh);
  }
  m_command.clear();
}
}  // namespace eng
