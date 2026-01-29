
#include "Component.h"
#include "GameObject.h"

namespace eng {
std::size_t Component::nextId = 1;

void Component::Init() {}
GameObject* Component::getOwner() {
  return m_owner;
}
ComponentFactory& ComponentFactory::GetInstance() {
  static ComponentFactory instance;
  return instance;
}
void Component::LoadProperties(const nlohmann::json& json) {}

}  // namespace eng
