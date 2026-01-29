#include "Game.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "Player.h"
#include "TestObject.h"
#include "physics/Collider.h"
#include "physics/RigidBody.h"
#include "scene/GameObject.h"
#include "scene/components/AnimationComponent.h"
#include "scene/components/LightComponent.h"
#include "scene/components/MeshComponent.h"
#include "scene/components/PhysicsComponent.h"
bool Game::Init() {
#if 0
  auto texture = eng::Texture::Load("brick.png");
  m_scene = new eng::Scene();

  eng::Engine::getInstance().setScene(m_scene);
  auto player = m_scene->CreateObject<Player>("Player");
  player->Init();
  m_scene->SetMainCamera(player);
  // m_scene->CreateObject<TestObject>("TestObject");

  auto material = eng::Material::Load("materials/brick.mat");
  auto mesh = eng::Mesh::CreateBox();
  // auto objectA = m_scene->createObject("objectA");
  // objectA->AddComponent(new eng::MeshComponent(material, mesh));
  // objectA->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
  // eng::Engine::getInstance().setScene(m_scene);

  //  auto objectB = m_scene->createObject("objectA");
  // objectB->AddComponent(new eng::MeshComponent(material, mesh));
  // objectB->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
  // objectB->SetRotation(glm::vec3(0.0f, 2.0f, 0.0f));

  // auto suzanneMesh = eng::Mesh::Load("models/Suzanne.gltf");
  // auto suzanneMaterial = eng::Material::Load("materials/suzanne.mat");

  // auto suzanneObj = m_scene->createObject("Suzanne");
  // suzanneObj->AddComponent(
  //    new eng::MeshComponent(suzanneMaterial, suzanneMesh));
  // suzanneObj->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
  auto suzanneObject = eng::GameObject::LoadGLTF("models/Suzanne.gltf");
  suzanneObject->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
  auto car = eng::GameObject::LoadGLTF("models/130/scene.gltf");
  car->SetPosition(glm::vec3(1.0f, 0.0f, 4.0f));
  car->SetScale(glm::vec3(3.0f, 3.0f, 3.0f));
  auto light = m_scene->createObject("Light");
  auto lightComp = new eng::LightComponent();
  lightComp->SetColor(glm::vec3(1.0f));
  light->AddComponent(lightComp);
  light->SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));

  auto ground = m_scene->createObject("Ground");
  ground->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));

  glm::vec3 groundExtents(20.0f, 2.0f, 20.0f);
  auto groundMesh = eng::Mesh::CreateBox(groundExtents);
  ground->AddComponent(new eng::MeshComponent(material, groundMesh));

  auto groundCollider = std::make_shared<eng::BoxCollider>(groundExtents);
  auto groundBody = std::make_shared<eng::RigidBody>(
      eng::BodyType::Static, groundCollider, 0.0f, 0.5f);
  ground->AddComponent(new eng::PhysicsComponent(groundBody));

  auto boxObj = m_scene->createObject("FallingBox");
  boxObj->AddComponent(new eng::MeshComponent(material, mesh));
  boxObj->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
  boxObj->SetRotation(glm::quat(glm::vec3(1.0f, 2.0f, 0.0f)));
  auto boxCollider = std::make_shared<eng::BoxCollider>(glm::vec3(1.0f));

  auto boxBody = std::make_shared<eng::RigidBody>(eng::BodyType::Dynamic,
                                                  boxCollider, 5.0f, 0.5f);
  boxObj->AddComponent(new eng::PhysicsComponent(boxBody));
#endif
  auto scene = eng::Scene::Load("scenes/scene.sc");
  m_scene = scene;
  eng::Engine::getInstance().setScene(scene);

  return true;
}
void Game::Update(float deltaTime) {
  m_scene->Update(deltaTime);
}
void Game::Destroy() {
  delete m_scene;
}
void Game::RegisterTypes() {
  Player::Register();
}
