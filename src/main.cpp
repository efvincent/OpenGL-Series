#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <alloca.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui_impl_glfw.h>
#include <iostream>
#include <stdexcept>
#include <csignal>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glAssert.hpp"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "renderer.hpp"
#include "tests/test.hpp"
#include "tests/testClearColor.hpp"
#include "tests/testTexture2D.hpp"

#pragma region setup and support

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    GLCall(glViewport(0,0,width,height));   
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow* setup() {
    GLFWwindow* window;
    int width{1200}, height{750};

    GLCall(
        if (!glfwInit())
            throw std::runtime_error("could not glfwInit()");
    );

    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

    GLCall(window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL));
    if (!window) {
        GLCall(glfwTerminate());
        throw std::runtime_error("could not glfwCreateWindow()");
    }

    // Make the window's context current
    GLCall(glfwMakeContextCurrent(window));

    GLCall(glViewport(0, 0, width, height));

    GLCall(glfwSetFramebufferSizeCallback(window, framebuffer_size_callback));

    // setting the swap interval to 1 synchronizes the frame rate to the refresh rate
    GLCall(glfwSwapInterval(1));

    // set alpha blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); 
    
    // ImGUI setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    if (glewInit() != GLEW_OK) {
      std::cerr << "Error initializing GLEW" << std::endl;
      throw std::runtime_error("could not glewInit()");
    };

    GLCall(std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl);
    return window;
}

#pragma endregion

int main(void)
{
    GLFWwindow* window = setup();
    
    Test::Test* currentTest = nullptr;
    Test::TestMenu* testMenu = new Test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->registerTest<Test::TestClearColor>("Clear Color");
    testMenu->registerTest<Test::TestTexture2D>("2D Texture");
    
    /*------------------------------------------*/
    /*------------- RENDER LOOP ----------------*/
    /*------------------------------------------*/

    while (!glfwWindowShouldClose(window))
    {
        Renderer::clear();

        ImGui_ImplOpenGL3_NewFrame();

        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        if (currentTest) {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if(currentTest != testMenu && ImGui::Button("<-")) {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        processInput(window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }
    delete currentTest;
    if (currentTest != testMenu) {
        delete testMenu;
    }

    /*------------- Clean up and end the program ----------------*/

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    GLCall(glfwTerminate());
    return 0;
}