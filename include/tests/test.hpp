#pragma once

namespace Test {
  class Test
  {
  public:
    Test() {};
    virtual ~Test() {};

    virtual void OnUpdate(float deltaTime) {} 
    virtual void OnRender() {}
    virtual void OnImGuiRender() {}
    virtual const char* testName() const { return "N/A"; };
  };
}