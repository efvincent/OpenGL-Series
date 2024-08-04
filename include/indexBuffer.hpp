#pragma once

#include <sys/types.h>

class IndexBuffer 
{
private:
  uint mRendererID;
  uint mCount;

public:
  IndexBuffer(const uint* data, uint count);
  ~IndexBuffer();
  void bind() const;
  void unbind() const;
  inline int count() const { return mCount; }
};