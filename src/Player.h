#pragma once
#include <eng.h>
#include "scene/GameObject.h"
#include "scene/components/AnimationComponent.h"
#include "scene/components/AudioComponent.h"
#include "scene/components/PlayerControllerComponent.h"

class Player : public eng::GameObject {
  GAMEOBJECT(Player)
 public:
  void Init() override;
  void update(float deltaTime) override;

 private:
  eng::AnimationComponent* m_animationComponent = nullptr;
  eng::AudioComponent* m_audioComponent = nullptr;
  eng::PlayerControllerComponent* m_playerControllerComponent = nullptr;
};
