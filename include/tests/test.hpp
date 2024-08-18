#pragma once

#include <vector>
#include <string>
#include <functional>

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
    TestMenu(Test*& currentTestPointer) 
      : m_currentTest(currentTestPointer) {};

    void OnImGuiRender() override;

    template<typename T>
    void registerTest(const std::string& name) {
      m_tests.push_back(std::make_pair(name, []() { return new T(); }));
    }


  private:
    std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;
    Test*& m_currentTest;
  };
}