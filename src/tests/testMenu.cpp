#include "tests/test.hpp"
#include <imgui.h> // Include the header file for ImGui

namespace Test {

void TestMenu::OnImGuiRender() {
  for(auto test : m_tests) {
    if (ImGui::Button(test.first.c_str())) {
      m_currentTest = test.second();
    }
  }
}

} // namespace Test