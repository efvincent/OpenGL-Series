#pragma once

#include <GL/glew.h>
#include <string>

#ifdef NDEBUG
#define ASSERT(condition) ((void)0)
#else
#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            debugBreak(); \
            std::abort(); \
        } \
    } while (0)
#endif


#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __LINE__, __FILE__))

void debugBreak();

std::string GetGLErrorString(GLenum errorCode);

void GLClearError();

bool GLLogCall(const char* call, int line, const char* filename);
