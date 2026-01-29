#pragma once
// This class is owned by the engine
#include <array>
#include <glm/vec2.hpp>
namespace eng {
class InputManager {
 private:
  InputManager() = default;
  InputManager(const InputManager&) = delete;
  InputManager(InputManager&&) = delete;
  InputManager& operator=(const InputManager&) = delete;
  InputManager& operator=(InputManager&) = delete;

 private:
  friend class Engine;

 public:
  void SetKeyPressed(int key, bool pressed);
  bool IsKeyPressed(int key);
  void SetMouseButtonPressed(int button, bool pressed);
  bool IsMouseButtonPressed(int button);

  void SetMousePositionOld(const glm::vec2& pos);
  const glm::vec2& GetMousePositionOld() const;
  void SetMousePositionCurrent(const glm::vec2& pos);
  const glm::vec2& GetMousePositioncurrent() const;

  void SetMousePositionChanged(bool changed);
  bool IsMousePositionChanged() const;

 private:
  std::array<bool, 256> m_keys = {false};
  std::array<bool, 16> m_mouseKeys = {false};
  glm::vec2 m_mousePositionOld = glm::vec2(0.0f);
  glm::vec2 m_mousePositionCurrent = glm::vec2(0.0f);

  bool m_mousePositionChanged = false;
};
}  // namespace eng
