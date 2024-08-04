// texture.cpp
#include "texture.hpp"
#include "vendor/stb_image.h"
#include <GL/glew.h>
#include "glAssert.hpp"

Texture::Texture(const std::string& path) 
      : mRenderId(0),
        mFilename(path), 
        mLocalBuffer(nullptr), 
        mWidth(0), 
        mHeight(0), 
        mBPP(0) 
{
    stbi_set_flip_vertically_on_load(1);
    mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);

    GLCall(glGenTextures(1, &mRenderId));             // generate a GL object
    GLCall(glBindTexture(GL_TEXTURE_2D, mRenderId));  // register it as a 2D texture

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));      // x dimension
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));      // y dimension

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (mLocalBuffer)
        stbi_image_free(mLocalBuffer);
}

Texture::~Texture() {
    glDeleteTextures(1, &mRenderId);
}

void Texture::bind(unsigned int slot) const {
  GLCall(glActiveTexture(GL_TEXTURE0 + slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, mRenderId));
}

void Texture::unbind() {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}