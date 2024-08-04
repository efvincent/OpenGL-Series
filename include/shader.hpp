#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <unordered_map>
#include <string>

class Shader {

public:
  Shader(const std::string& filename);
  ~Shader();

  void bind();
  void unbind();

  int getUniformLocation(const std::string& name);

  // set uniforms
  void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void setUniform1f(const std::string& name, float v0);
  void setUniform1i(const std::string& name, int v0);
  void setUniformMat4(const std::string& name, const glm::mat4 matrix);

private:
  std::string mFilename;
  uint mRenderId;
  std::unordered_map<std::string, int> mUniformLocationCache{};
  bool isBound;
  void checkBinding(const std::string& name) const;
};