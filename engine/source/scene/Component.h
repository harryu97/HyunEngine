#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
namespace eng {
class GameObject;
class Component {
 public:
  virtual ~Component() = default;
  virtual void LoadProperties(const nlohmann::json& json);

  virtual void Init();
  virtual void Update(float deltaTime) = 0;
  virtual size_t GetTypeId() const = 0;
  GameObject* getOwner();

  // each distinct get unique stable id
  template <typename T>
  static std::size_t StaticTypeId() {
    static size_t typeId = nextId++;
    return typeId;
  }

 protected:
  GameObject* m_owner = nullptr;

  friend class GameObject;

 private:
  // light alternative to RTTI
  static std::size_t nextId;
};
class ComponentCreatorBase {
 public:
  virtual ~ComponentCreatorBase() = default;
  virtual Component* CreateComponent() = 0;
};

template <typename T>
class ComponentCreator : public ComponentCreatorBase {
 public:
  Component* CreateComponent() override { return new T(); }
};
class ComponentFactory {
 public:
  static ComponentFactory& GetInstance();
  template <typename T>
  void RegisterComponent(const std::string& name) {
    m_creators.emplace(name, std::make_unique<ComponentCreator<T>>());
  }
  Component* CreateComponent(const std::string& name) {
    auto it = m_creators.find(name);
    if (it != m_creators.end()) {
      return it->second->CreateComponent();
    }
    return nullptr;
  }

 private:
  std::unordered_map<std::string, std::unique_ptr<ComponentCreatorBase>>
      m_creators;
};

#define COMPONENT(ComponentClass)                                           \
 public:                                                                    \
  static size_t TypeId() {                                                  \
    return eng::Component::StaticTypeId<ComponentClass>();                  \
  }                                                                         \
  size_t GetTypeId() const override {                                       \
    return TypeId();                                                        \
  }                                                                         \
  static void Register() {                                                  \
    eng::ComponentFactory::GetInstance().RegisterComponent<ComponentClass>( \
        std::string(#ComponentClass));                                      \
  }
}  // namespace eng
// namespace eng
