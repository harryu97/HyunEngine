#include "Application.h"
namespace eng {
void Application::SetNeedsToBeClosed(bool value) {
  m_needsToBeClosed = value;
}

bool Application::NeedsTobeClosed() const {
  return m_needsToBeClosed;
}

void Application::RegisterTypes() {}
}  // namespace eng
