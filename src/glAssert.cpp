#include "glAssert.hpp"
#include <csignal>
#include <string>
#include <iostream>

std::string GetGLErrorString(GLenum errorCode) {
    switch (errorCode) {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_CONTEXT_LOST:
            return "GL_CONTEXT_LOST";
        default:
            return "Unknown Error";
    }
}

void debugBreak() {
#if defined(_MSC_VER)
    // MSVC
    __debugbreak();
#elif defined(__clang__) || defined(__GNUC__)
    // Clang/LLVM or GCC
    #if defined(__i386__) || defined(__x86_64__)
        // x86/x64 architecture
        raise(SIGTRAP);
    #elif defined(__arm__) || defined(__aarch64__)
        // ARM architecture
        __asm__ __volatile__(".inst 0xd4200000"); // ARM breakpoint instruction
    #else
        #include <signal.h>
        raise(SIGTRAP); // Fallback for other architectures
    #endif
#else
    #include <signal.h>
    raise(SIGTRAP); // Fallback for unknown compilers
#endif
}

/**
 * @brief clear all errors, tossing them if there are any 
 */
void GLClearError() {
    while(glGetError() != GL_NO_ERROR);
}

/**
 * @brief retrieve all errors, ripping them out to the console for now 
 */
bool GLLogCall(const char* call, int line, const char* filename) {
    while (GLenum error = glGetError()) {
        std::cerr << "[OpenGL Error] " << GetGLErrorString(error) << " (" << error << "): " 
        << call << "\n at " << filename << ":" << line << std::endl;
        return false;
    }
    return true;
}
