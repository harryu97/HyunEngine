#pragma once
#include "../engine/source/eng.h"

class TestObject : public eng::GameObject {
 public:
  TestObject();
  void update(float deltaTime) override;

 private:
};
