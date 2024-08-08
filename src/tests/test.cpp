#include "tests/test.hpp"
#include "tests/testClearColor.hpp"
#include <imgui.h>
#include <utility>
#include <spdlog/spdlog.h>

namespace Test {

  TestMenu::TestMenu() 
    : m_current_test{nullptr}
  {
    m_tests.push_back(std::make_pair("Clear Color 1", []() { return new TestClearColor(); }));
    m_tests.push_back(std::make_pair("Clear Color 2", []() { return new TestClearColor(); }));
  }

  TestMenu::~TestMenu() {
    spdlog::trace("Test Menu Destructor");
  }

  void TestMenu::OnUpdate(float deltaTime) { }

  void TestMenu::OnRender() { 

  }

  void TestMenu::OnImGuiRender() {
    ImGui::Begin("Test Menu");
    if (m_current_test) {
      if (ImGui::Selectable("Close test")) {
        m_current_test = nullptr;
      } 
    } else {
      for(const auto& test : m_tests) {
        if (ImGui::Selectable(test.first.c_str())) {
          m_current_test = test.second();
        }
      }
    }
    ImGui::End();
  }
}