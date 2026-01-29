#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <type_traits>
#include <vector>
#include "Component.h"
namespace eng {
class Scene;
class GameObject {
 public:
  virtual ~GameObject() = default;

  virtual void Init();
  virtual void LoadProperties(const nlohmann::json& json);
  virtual void update(float deltaTime);
  const std::string& GetName() const;
  void SetName(const std::string& name);
  GameObject* getParent();
  bool SetParent(GameObject* parent);
  Scene* GetScene();
  // Checking if the object is alive
  bool isAlive() const;
  // Marking object to destroy
  void MarkForDestory();
  // Adding component
  void AddComponent(Component* component);

  void SetActive(bool active);
  bool isActive() const;

  template <typename T,
            typename = typename std::enable_if<std::is_base_of_v<Component, T>>>
  T* GetComponent() {
    size_t typeID = Component::StaticTypeId<T>();
    for (auto component : m_component) {
      if (component->GetTypeId() == typeID) {
        return static_cast<T*>(component);
      }
    }
    return nullptr;
  }
  GameObject* FindChildByName(const std::string& name);
  const glm::vec3& GetPosition() const;
  glm::vec3 GetWorldPosition() const;
  void SetWorldPosition(const glm::vec3& pos);

  void SetPosition(const glm::vec3& pos);

  const glm::quat& GetRotation() const;
  glm::quat GetWorldRotation();
  void SetRotation(const glm::quat& rot);
  void SetWorldRotation(const glm::quat& rot);

  const glm::vec3& GetScale() const;
  void SetScale(const glm::vec3& scale);

  glm::mat4 GetLocalTransform() const;
  glm::mat4 GetWorldTransform() const;

  static GameObject* LoadGLTF(const std::string& path, Scene* scene);

 protected:
  GameObject() = default;

 protected:
  std::string m_name;
  GameObject* m_parent = nullptr;
  Scene* m_scene = nullptr;
  std::vector<GameObject*> m_children;
  std::vector<Component*> m_component;

  bool m_isAlive = true;
  glm::vec3 m_position = glm::vec3(0.0f);
  glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
  glm::vec3 m_scale = glm::vec3(1.0f);
  bool m_isActive = true;

  friend class Scene;
};

class ObjectCreatorBase {
 public:
  virtual ~ObjectCreatorBase() = default;
  virtual GameObject* CreateGameObject() = 0;
};
template <typename T>
class ObjectCreator : public ObjectCreatorBase {
 public:
  virtual GameObject* CreateGameObject() override { return new T(); }
};
class GameObjectFactory {
 public:
  static GameObjectFactory& GetInstance();
  template <typename T>
  void RegisterObject(const std::string& name) {
    m_creators.emplace(name, std::make_unique<ObjectCreator<T>>());
  }
  GameObject* CreateGameObject(const std::string& typeName);

 private:
  std::unordered_map<std::string, std::unique_ptr<ObjectCreatorBase>>
      m_creators;
};
#define GAMEOBJECT(ObjectClass)                                        \
 public:                                                               \
  static void Register() {                                             \
    eng::GameObjectFactory::GetInstance().RegisterObject<ObjectClass>( \
        std::string(#ObjectClass));                                    \
  }
}  // namespace eng
// namespace eng
