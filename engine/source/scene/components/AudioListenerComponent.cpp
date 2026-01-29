#include "AudioListenerComponent.h"
#include "../GameObject.h"
#include "Engine.h"
namespace eng {
void AudioListenerComponent::Update(float deltaTime) {
  auto pos = m_owner->GetWorldPosition();
  Engine::getInstance().getAudioManager().SetListenerPosition(pos);
}
}  // namespace eng
