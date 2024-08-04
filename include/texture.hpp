#pragma once
#include <string>

class Texture {
private:
  uint mRenderId;
  std::string mFilename;
  unsigned char* mLocalBuffer;
  int mWidth{0}, mHeight{0}, mBPP;  
public:
  Texture(const std::string& path);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unbind();

  inline int witdh() { return mWidth; }
  inline int height() { return mHeight; }
  inline unsigned char* localBuffer() { return mLocalBuffer; }
};