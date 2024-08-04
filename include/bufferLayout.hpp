#pragma once

#include <stdexcept>
#include <sys/types.h>
#include <vector>
#include "glAssert.hpp"

struct VertexBufferElement {
  uint type;
  uint count;
  int normalized;
  static uint GetSizeOfType(uint type) {
    switch(type) {
      case GL_FLOAT: return 4;
      case GL_UNSIGNED_INT: return 4;
      case GL_UNSIGNED_BYTE: return 1;
    }
    ASSERT(false);
    return 0;
  }
};

class BufferLayout {
private:
  std::vector<VertexBufferElement> mElements;
  uint mStride;
public:
  BufferLayout();
  ~BufferLayout();
  
  template<typename T>
  void push(uint count) {
    std::runtime_error("type not supported");
  }
  
  inline uint getStride() const {
    return mStride;
  }

  inline const std::vector<VertexBufferElement>& getElements() const  {
    return mElements;
  }
};