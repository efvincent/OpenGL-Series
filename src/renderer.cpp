#include "renderer.hpp"

Renderer::Renderer() {
    // Constructor implementation
}

Renderer::~Renderer() {
    // Destructor implementation
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib,  Shader& shader) {
    shader.bind();
    va.bind();
    ib.bind();
    
    GLCall(glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}