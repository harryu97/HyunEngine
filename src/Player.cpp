#include "Player.h"
#include <iostream>
#include <memory>
#include "Bullet.h"
#include "GLFW/glfw3.h"
#include "glm/detail/type_vec.hpp"
#include "physics/Collider.h"
#include "physics/RigidBody.h"
#include "render/Material.h"
#include "render/Mesh.h"
#include "scene/GameObject.h"
#include "scene/components/AnimationComponent.h"
#include "scene/components/AudioComponent.h"
#include "scene/components/PlayerControllerComponent.h"
void Player::Init() {
  // AddComponent(new eng::CameraComponent());
  // SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
  // AddComponent(new eng::PlayerControllerComponent());

  // auto gun =
  //    eng::GameObject::LoadGLTF("models/sten_gunmachine_carbine/scene.gltf");
  // attach the gun to camera
  // gun->SetParent(this);
  // gun->SetPosition(glm::vec3(0.7f, -0.5f, -0.75f));
  //  getParentun->SetScale(glm::vec3(-1.0f, 1.0f, 1.0f));
  // if (auto anim = gun->GetComponent<eng::AnimationComponent>())
  {
    if (auto bullet = FindChildByName("bullet_33")) {
      bullet->SetActive(false);
    }
    if (auto fire = FindChildByName("BOOM_35")) {
      fire->SetActive(false);
    }
    // anim->Play("shoot", false);
  }
  if (auto gun = FindChildByName("Gun")) {
    std::cout << "Found gun" << std::endl;
    m_animationComponent = gun->GetComponent<eng::AnimationComponent>();
    if (!m_animationComponent) {
      std::cout << "NO ANIM GUN" << std::endl;
    }
  }

  m_audioComponent = GetComponent<eng::AudioComponent>();
  m_playerControllerComponent = GetComponent<eng::PlayerControllerComponent>();
}

void Player::update(float deltaTime) {
  if (auto gun = FindChildByName("Gun")) {
    std::cout << "THIS GUN" << std::endl;
  }
  eng::GameObject::update(deltaTime);
  auto& input = eng::Engine::getInstance().getInputManager();
  if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
    if (m_animationComponent && !m_animationComponent->isPlaying()) {
      m_animationComponent->Play("shoot", false);
      if (m_audioComponent) {
        if (m_audioComponent->IsPlaying("shoot")) {
          m_audioComponent->Stop("shoot");
        }
        m_audioComponent->Play("shoot");
      }

      auto bullet = m_scene->CreateObject<Bullet>("Bullet");
      auto material = eng::Material::Load("materials/suzanne.mat");
      auto mesh = eng::Mesh::CreateSphere(0.2f, 32, 32);
      bullet->AddComponent(new eng::MeshComponent(material, mesh));

      glm::vec3 pos = glm::vec3(0.0f);
      if (auto child = FindChildByName("BOOM_35")) {
        pos = child->GetWorldPosition();
      }

      bullet->SetPosition(pos + m_rotation * glm::vec3(-0.2f, 0.2f, -1.75f));
      auto collider = std::make_shared<eng::SphereCollider>(0.2f);
      auto rigidBody = std::make_shared<eng::RigidBody>(eng::BodyType::Dynamic,
                                                        collider, 10.0f, 0.1f);
      bullet->AddComponent(new eng::PhysicsComponent(rigidBody));
      glm::vec3 front = m_rotation * glm::vec3(0.0f, 0.0f, -1.0f);
      rigidBody->ApplyImpulse(front * 500.0f);
    }
  }
  if (input.IsKeyPressed(GLFW_KEY_SPACE)) {
    std::cout << "Jump pressed" << std::endl;
    if (m_audioComponent && !m_audioComponent->IsPlaying("jump")) {
      m_audioComponent->Play("jump");
    }
  }
  bool walking =
      input.IsKeyPressed(GLFW_KEY_W) || input.IsKeyPressed(GLFW_KEY_A) ||
      input.IsKeyPressed(GLFW_KEY_S) || input.IsKeyPressed(GLFW_KEY_D);
  if (walking && m_playerControllerComponent &&
      m_playerControllerComponent->OnGround()) {
    if (m_audioComponent && !m_audioComponent->IsPlaying("step")) {
      std::cout << ">>> STARTING step sound <<<" << std::endl;
      m_audioComponent->Play("step", true);
    }
  } else {
    if (m_audioComponent && m_audioComponent->IsPlaying("step")) {
      std::cout << ">>> STOPPING step sound <<<" << std::endl;
      m_audioComponent->Stop("step");
    }
  }
}
