#pragma once
#include "../Component.h"
namespace eng {
class AudioListenerComponent : public Component {
  COMPONENT(AudioListenerComponent)
 public:
  void Update(float deltaTime) override;
};
}  // namespace eng
