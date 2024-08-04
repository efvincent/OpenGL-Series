#include "shader.hpp"
#include "shaderCompiler.hpp"
#include "glAssert.hpp"
// #ifdef DEBUG
#include <iostream>
// #endif

Shader::Shader(const std::string& filename) 
  : mFilename(filename)
  , mRenderId(0)
  , isBound(false) 
{ 
  auto source = parseShader(mFilename);
  mRenderId = createShaderProgram(source.vertexSource, source.fragmentSource);
  bind();
}

Shader::~Shader() { 
  if (mRenderId != 0)
    GLCall(glDeleteProgram(mRenderId));
}

void Shader::checkBinding(const std::string& name) const {
  // #ifdef DEBUG
  if (!isBound) {
    std::cerr << "ERROR: Cannot set uniform " << name << ": shader is not bound!" << std::endl;
  }
  // #endif
}

void Shader::setUniform4f(
    const std::string& name, float v0, float v1, float v2, float v3) 
{ 
  GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1f(const std::string& name, float v0) {
  GLCall(glUniform1f(getUniformLocation(name), v0));
}

void Shader::setUniform1i(const std::string& name, int v0) {
  GLCall(glUniform1i(getUniformLocation(name), v0));
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4 matrix) {
  GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string& name) {
  if (mUniformLocationCache.find(name) != mUniformLocationCache.end()) {
    return mUniformLocationCache[name];
  }

  GLCall(int loc = glGetUniformLocation(mRenderId, name.c_str()));
  // #ifdef DEBUG
  if (loc == -1) {
    std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
  }  
  // #endif
  mUniformLocationCache[name] = loc;
  return loc;
}

void Shader::bind() {
  GLCall(glUseProgram(mRenderId));
  isBound = true;
}

void Shader::unbind() {
  GLCall(glUseProgram(0)); 
  isBound = false;
}