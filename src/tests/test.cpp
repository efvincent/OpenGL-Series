#include "tests/test.hpp"
#include "tests/testClearColor.hpp"

namespace Test {

  TestMenu::TestMenu() 
  {
    TestClearColor t = TestClearColor();
    m_tests.push_back(std::make_pair("Clear Color", []() { return new TestClearColor(); }));
  }

  TestMenu::~TestMenu() {

  }

  void TestMenu::OnUpdate(float deltaTime) { }

  void TestMenu::OnRender() { }

  void TestMenu::OnImGuiRender() { }
}