#pragma once
#include <eng.h>
#include "scene/GameObject.h"

class Bullet : public eng::GameObject {
  GAMEOBJECT(Bullet)
 public:
  void update(float deltaTime) override;

 private:
  float m_lifeTime = 2.0f;
};
