#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <alloca.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui_impl_glfw.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <csignal>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glAssert.hpp"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "indexBuffer.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include "bufferLayout.hpp"
#include "texture.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    GLCall(glViewport(0,0,width,height));   
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void imguiSetup(GLFWwindow* window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

GLFWwindow* setup() {
    GLFWwindow* window;
    GLCall(
        if (!glfwInit())
            throw std::runtime_error("could not glfwInit()");
    );

    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

    GLCall(window = glfwCreateWindow(1200, 750, "OpenGL", NULL, NULL));
    if (!window) {
        GLCall(glfwTerminate());
        throw std::runtime_error("could not glfwCreateWindow()");
    }

    // Make the window's context current
    GLCall(glfwMakeContextCurrent(window));

    // GLCall(glViewport(0, 0, 1200, 750));

    //GLCall(glfwSetFramebufferSizeCallback(window, framebuffer_size_callback));

    // setting the swap interval to 1 synchronizes the frame rate to the refresh rate
    GLCall(glfwSwapInterval(1));

    imguiSetup(window);

    // set alpha blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); 
    
    if (glewInit() != GLEW_OK) {
      std::cerr << "Error initializing GLEW" << std::endl;
      throw std::runtime_error("could not glewInit()");
    };

    GLCall(std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl);
    return window;
}

int main(void)
{
    IMGUI_CHECKVERSION();
    GLFWwindow* window = setup();


    /*--------- Animation state -----------*/

    float texturePicker = 0.0f;
    float increment = 0.02f; 
    float incDelta = 0.02f;

    /*--------- Vertex Buffer -----------*/
    
    float verticies[] = { 
        -0.5f, -0.5f, 0.0f, 0.0f,   // 0: bottom left
         0.5f, -0.5f, 1.0f, 0.0f,   // 1: bottom right
         0.5f,  0.5f, 1.0f, 1.0f,   // 2: top right
        -0.5f,  0.5f, 0.0f, 1.0f    // 3
    };

    VertexBuffer vertexBuffer(verticies, sizeof(verticies));

    /*---------- Vertex Array -----------*/
    // links the vertex buffer with a layout

    BufferLayout layout;
    layout.push<float>(2);  
    layout.push<float>(2);
    
    VertexArray vertexArray;
    vertexArray.addBuffer(vertexBuffer, layout);

    /*--------- Vertex Index Buffer -----------*/

    uint indices[] = {      // two triangles 
        0, 1, 2, 
        2, 3, 0 };
        
    IndexBuffer indexBuffer(indices, sizeof(indices) / sizeof(indices[0]));

    /*----------- Shader Program ----------------*/

    auto shader = Shader("../res/shaders/basic.shader");
    shader.bind();

    /*------------- Transforms ---------------*/
    // converts the verticies to screen coordinates.
    glm::mat4 proj = glm::ortho(
        -2.0f,      // left
         2.0f,      // right
        -1.5f,      // bottom
         1.5f,      // top
        -1.0f,      // zNear
         1.0f);     // zFar

    // translate the identity matrix
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(texturePicker,0,0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));
    auto mvpMatrix = proj * view * model;
    shader.setUniformMat4("u_mvpMatrix", mvpMatrix);

    /*------------- Textures ---------------*/

    // load a texture and bind it to slot zero, then set the
    // uniform for the shader to that slot
    Texture texture1("../res/textures/ChernoLogo.png");
    Texture texture2("../res/textures/HazelLogo.png");
    texture1.bind(0);
    texture2.bind(1);   
    shader.setUniform1i("u_Texture", 0);

    /*------------- ImGui window state ---------------*/

    bool rotate = true;
    float rotation = texturePicker;
    bool show_playground_window = true;
    bool show_plot_window = true;
    bool show_knob_window = true;
    ImVec4 clear_color = ImVec4(0.168f, 0.394f, 0.534f, 1.00f);
    float e1x{1}, e1y{1};

    /*------------------------------------------*/
    /*------------- RENDER LOOP ----------------*/
    /*------------------------------------------*/

    while (!glfwWindowShouldClose(window))
    {
        Renderer::clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /*------------- Input handler ----------------*/
        processInput(window);

        /*------------- animate texture ----------------*/
        
        if (increment > 0.0f && texturePicker > 1.0f) increment = incDelta * -1.0f;
        else if (increment < 0.0f && texturePicker < -1.0f) increment = incDelta;
        else if (increment > 0.0f) increment = incDelta;
        else increment = -incDelta;

        texturePicker += increment;
        if (rotate) rotation += increment;
        int textureSlot = texturePicker > 0.0f ? 0 : 1;

        /*------ Set fixed matricies & uniforms -------*/

        shader.bind();
        shader.setUniform1i("u_Texture", textureSlot);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(texturePicker,0,0));
        
        /*------------- Draw element 1 ----------------*/

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(e1x, e1y, 0));
            glm::mat4 mvpMatrix = proj * glm::mat4(1) * model;
            shader.setUniformMat4("u_mvpMatrix", mvpMatrix);
            
            Renderer::draw(vertexArray, indexBuffer, shader);
        }
        /*------------- Draw element 2 ----------------*/
        {
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(texturePicker,0,0));
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, texturePicker, 0));
            model = glm::rotate(model, rotation, glm::vec3(0,0,1));
            glm::mat4 mvpMatrix = proj * view * model;
            shader.setUniformMat4("u_mvpMatrix", mvpMatrix);
            
            Renderer::draw(vertexArray, indexBuffer, shader);
        }
        
        /*------------- Display Controls ----------------*/

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Settings");

            ImGui::Text("Configure the App below.");              
            ImGui::Checkbox("Rotate?", &rotate);      
            ImGui::SliderFloat("Move speed", &incDelta, 0.0f, 0.1f);  
            ImGui::SliderFloat("Element 1 X", &e1x, -1.0f, 1.0f);  
            ImGui::SliderFloat("Element 2 Y", &e1y, -1.0f, 1.0f);  

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        /*------- Swap buffers, poll events ----------*/

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