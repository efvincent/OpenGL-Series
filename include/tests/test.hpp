#pragma once
#include <functional>
#include <vector>
#include <string>

namespace Test {
  class Test
  {
  public:
    Test() {};
    virtual ~Test() {};

    virtual void OnUpdate(float deltaTime) {} 
    virtual void OnRender() {}
    virtual void OnImGuiRender() {}
  };

  class TestMenu : public Test {
  public: 
    TestMenu();
    ~TestMenu();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;
  private:
    Test m_current_test;
    std::vector<std::pair<std::string, std::function<Test*>>> m_tests;
  };
}