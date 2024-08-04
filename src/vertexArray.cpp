#include "vertexArray.hpp"
#include "bufferLayout.hpp"
#include "glAssert.hpp"
#include "vertexBuffer.hpp"

VertexArray::VertexArray() {
  GLCall(glGenVertexArrays(1, &mRenderId));
}

VertexArray::~VertexArray() {
  GLCall(glDeleteVertexArrays(1, &mRenderId));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const BufferLayout& layout) {
  this->bind();
  vb.bind();
  uint offset = 0;
  const auto& elements = layout.getElements();
  for (uint i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];
    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(
      i, 
      element.count, 
      element.type, 
      element.normalized, 
      layout.getStride(), 
      reinterpret_cast<const void*>(offset)));
    offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
  }
}

void VertexArray::bind() const {
  GLCall(glBindVertexArray(mRenderId));
}

void VertexArray::unbind() const {
  GLCall(glBindVertexArray(0));
}