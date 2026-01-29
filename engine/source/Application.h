#pragma once
namespace eng {

class Application {
 public:
  virtual ~Application() = default;
  virtual bool Init() = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void Destroy() = 0;
  virtual void RegisterTypes();
  void SetNeedsToBeClosed(bool value);
  bool NeedsTobeClosed() const;

 private:
  bool m_needsToBeClosed = false;
};

}  // namespace eng
