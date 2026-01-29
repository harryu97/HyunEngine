#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "Common.h"
#include "GameObject.h"
namespace eng {
class GameObject;
class Scene {
 public:
  static void RegisterTypes();
  void Update(float deltaTime);
  void Clear();
  GameObject* createObject(const std::string& name,
                           GameObject* parent = nullptr);
  GameObject* createObject(const std::string& type,
                           const std::string& name,
                           GameObject* parent = nullptr);
  // template for creating object for derived GameObject types.
  template <
      typename T,
      typename = typename std::enable_if_t<std::is_base_of_v<GameObject, T>>>
  T* CreateObject(const std::string& name, GameObject* parent = nullptr) {
    auto* obj = new T();
    obj->SetName(name);
    obj->m_scene = this;
    if (m_isUpdating) {
      m_objectsToAdd.push_back({obj, parent});
    } else {
      SetParent(obj, parent);
    }
    return obj;
  }

  bool SetParent(GameObject* obj, GameObject* parent);

  void SetMainCamera(GameObject* camera);
  GameObject* getCamera();

  // Light
  std::vector<LightData> CollectLights();
  static Scene* Load(const std::string& path);

 private:
  void CollectLightRecursive(GameObject* obj, std::vector<LightData>& out);

  void LoadObject(const nlohmann::json& jsonObject, GameObject* parent);

 private:
  std::vector<GameObject*> m_objects;
  std::vector<std::pair<GameObject*, GameObject*>> m_objectsToAdd;
  GameObject* m_mainCamera = nullptr;
  bool m_isUpdating = false;
};
}  // namespace eng
