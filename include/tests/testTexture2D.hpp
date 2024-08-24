#pragma once

#include "test.hpp"

namespace Test {

  class TestTexture2D : public Test
  {
  public:
    TestTexture2D();
    ~TestTexture2D();
  
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;
  
  private:
    float m_color[4];
  
  };

}