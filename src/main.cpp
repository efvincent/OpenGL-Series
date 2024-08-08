#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <alloca.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui_impl_glfw.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <csignal>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glAssert.hpp"
#include <imgui.h>
#include <vector>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "renderer.hpp"
#include "tests/test.hpp"

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

    // ImGUI setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
    ImGui::StyleColorsDark();

    // set alpha blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); 
    
    if (glewInit() != GLEW_OK) {
      std::cerr << "Error initializing GLEW" << std::endl;
      throw std::runtime_error("could not glewInit()");
    };

    // GLCall(std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl);
    return window;
}

int main(void)
{
    GLFWwindow* window = setup();

    std::vector<std::unique_ptr<Test::Test>> tests;
    tests.push_back(std::make_unique<Test::TestMenu>());

    Test::TestMenu menu; 

    /*------------------------------------------*/
    /*------------- RENDER LOOP ----------------*/
    /*------------------------------------------*/

    while (!glfwWindowShouldClose(window))
    {
        Renderer::clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        menu.OnUpdate(0.0f);
        menu.OnRender();
        menu.OnImGuiRender();        

        /*------------- Input handler ----------------*/
        processInput(window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    /*------------- Clean up and end the program ----------------*/
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    GLCall(glfwTerminate());
    return 0;
}