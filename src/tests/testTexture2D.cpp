#include "tests/testTexture2D.hpp"
#include "glAssert.hpp"
#include <imgui.h> 

namespace Test {

    TestTexture2D::TestTexture2D()
      : m_color { 0.2f, 0.3f, 0.8f, 1.0f } {}

    TestTexture2D::~TestTexture2D() { }

    void TestTexture2D::OnUpdate(float deltaTime) { }

    void TestTexture2D::OnRender() {
      GLCall(glClearColor(0,0,0,0));
      GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestTexture2D::OnImGuiRender() { 

    }

}