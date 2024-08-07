#pragma once

#include "test.hpp"

namespace Test {

  class TestClearColor : public Test
  {
  public:
    TestClearColor();
    ~TestClearColor();
  
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;
  
  private:
    float m_color[4];
  
  };

}