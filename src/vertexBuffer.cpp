#include "vertexBuffer.hpp"
#include "glAssert.hpp"

// note: creating the vertex buffer, enabling it, setting it's layout 
// (with glVertextAttribPointer), and binding it's name to the buffer 
// data, automatically enlists it in the bound vertex array object (vao).
// the same holds for Vertex Index Buffer below.
//
// this means we can unbind them (by calling glBindVertexArray and glBindBuffer with
// object names zero (0)) and the vao will still have the link between the vertex
// array, it's layout, and the index array.

VertexBuffer::VertexBuffer(const void* data, size_t size) {
    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &mRendererID));
}

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
}

void VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}