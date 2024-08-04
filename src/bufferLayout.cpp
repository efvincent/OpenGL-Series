#include "bufferLayout.hpp"

BufferLayout::BufferLayout() : mStride(0) { }

BufferLayout::~BufferLayout() { }


template<>
void BufferLayout::push<float>(uint count) {
  mElements.push_back({GL_FLOAT, count, GL_FALSE});
  mStride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
void BufferLayout::push<uint>(uint count) {
  mElements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  mStride += count *  VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void BufferLayout::push<u_char>(uint count) {
  mElements.push_back({GL_UNSIGNED_BYTE, count, GL_FALSE});
  mStride += count *  VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
