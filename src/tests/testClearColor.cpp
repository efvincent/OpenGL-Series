#include "tests/testClearColor.hpp"
#include "glAssert.hpp"
#include <imgui.h> 
#include <spdlog/spdlog.h>

namespace Test {

    TestClearColor::TestClearColor()
      : m_color { 0.2f, 0.3f, 0.8f, 1.0f } {}

    TestClearColor::~TestClearColor() { 
      spdlog::trace("TestClearColor Destructor");
    }

    void TestClearColor::OnUpdate(float deltaTime) { }

    void TestClearColor::OnRender() {
      GLCall(glClearColor(m_color[0], m_color[1], m_color[2], m_color[3]));
      GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImGuiRender() { 
      ImGui::ColorEdit4("Clear Color", m_color);
    }

}