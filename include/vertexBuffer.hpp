#pragma once

#include <sys/types.h>

class VertexBuffer 
{
private:
  uint mRendererID;

public:
  VertexBuffer(const void* data, size_t size);
  ~VertexBuffer();
  void bind() const;
  void unbind() const;
};