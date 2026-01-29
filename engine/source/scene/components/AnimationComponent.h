#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>
#include <vector>
#include "../Component.h"

namespace eng {

struct KeyFrameVec3 {
  float time = 0.0f;
  glm::vec3 value = glm::vec3(0.0f);
};
struct KeyFrameQuat {
  float time = 0.0f;
  glm::quat value = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
};
struct TransformTrack {
  std::string targetName;
  std::vector<KeyFrameVec3> positions;
  std::vector<KeyFrameQuat> rotations;
  std::vector<KeyFrameVec3> scales;
};
struct AnimationClip {
  std::string name;
  float duration = 0.0f;
  bool looping = true;
  std::vector<TransformTrack> tracks;
};
// We need fast mapping to game object
struct ObjectBinding {
  GameObject* object = nullptr;
  std::vector<size_t> trackIndices;
};
class AnimationComponent : public Component {
  COMPONENT(AnimationComponent)
 public:
  void Update(float deltaTime) override;
  void SetClip(AnimationClip* clip);
  void RegisterClip(const std::string& name, AnimationClip* clip);
  void Play(const std::string& name, bool loop = true);
  bool isPlaying() const;

 private:
 private:
  void BuildBindings();
  glm::vec3 InterPolate(const std::vector<KeyFrameVec3>& keys, float time);
  glm::quat InterPolate(const std::vector<KeyFrameQuat>& keys, float time);

  AnimationClip* m_clip = nullptr;
  float m_time = 0.0f;
  bool m_looping = true;
  bool m_isPlaying = false;
  std::unordered_map<std::string, AnimationClip*> m_clips;
  std::unordered_map<GameObject*, ObjectBinding*> m_bindings;
};
}  // namespace eng
