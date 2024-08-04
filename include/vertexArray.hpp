#pragma once

#include <sys/types.h>
#include "bufferLayout.hpp"
#include "vertexBuffer.hpp"
#include "glAssert.hpp"

class VertexArray {
private:
  uint mRenderId;

public:
  VertexArray();
  ~VertexArray();
  void addBuffer(const VertexBuffer& vb, const BufferLayout& layout);
  void bind() const;
  void unbind() const;
  inline uint getID() const { return mRenderId; }
};