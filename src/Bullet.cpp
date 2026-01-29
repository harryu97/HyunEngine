#include "Bullet.h"
#include "scene/GameObject.h"
void Bullet::update(float deltaTime) {
  eng::GameObject::update(deltaTime);
  m_lifeTime -= deltaTime;
  if (m_lifeTime <= 0.0f) {
    MarkForDestory();
  }
}
