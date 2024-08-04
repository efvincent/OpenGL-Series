#include "indexBuffer.hpp"
#include "glAssert.hpp"


IndexBuffer::IndexBuffer(const uint* data, const uint count) : mCount(count) {
    ASSERT(sizeof(uint) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &mRendererID));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
}

void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}