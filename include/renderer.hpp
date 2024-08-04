#pragma once

#include "indexBuffer.hpp"
#include "shader.hpp"
#include "vertexArray.hpp"

class Renderer {
private:
public:
  Renderer();
  ~Renderer();
  static void clear();
  static void draw(const VertexArray& va, const IndexBuffer& ib,  Shader& shader);
};