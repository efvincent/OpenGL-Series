#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <alloca.h>
#include <iostream>
#include <csignal>
#include <stdexcept>
#include "glAssert.hpp"
#include "shaderCompiler.hpp"

ShaderProgramSource parseShader(const std::string& filename) {
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::ifstream stream(filename);
    if (!stream.is_open()) {
        throw std::runtime_error("failed to open shader source: " + filename);
    }
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << "\n";
        }
    }
    return {
        ss[0].str(),
        ss[1].str()
    };
}

 unsigned int compileShaderProgram(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // get the result of the compilation. the "iv" at the end of the call
    // to glGetShader means:
    // i = integer
    // v = vector (ie array, or pointer)
    // this means this version of the function expects an integer in the
    // second parameter, and a pointer in the first.
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);    
    if (result != GL_TRUE) {
        GLsizei length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // char* message = (char*)alloca(length * sizeof(char));
        GLchar message[1024];
        glGetShaderInfoLog(id, 1024, &length, message);
        auto shaderType = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
        std::cerr << "Failed to compile " << shaderType << " (log length = " << length << ") shader:\n" << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShaderProgram(GL_VERTEX_SHADER, vertexShader); 
    unsigned int ss = compileShaderProgram(GL_FRAGMENT_SHADER, fragmentShader);

    // attach compiled shader code to the program. Similar to the fact that we link
    // all the object files together with a linker, with GL we attach compiled shaders
    // (think shader object files) to a single thing (the program), and then we can
    // have GL "link the program" which links all the shaders defined in the program to
    // a single compiled and linked shader program
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, ss));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    // after linking, we can delete the shaders. They're the equiv of object files, and
    // we don't need them after they've been linked and validated.
    GLCall(glDetachShader(program, vs));
    GLCall(glDetachShader(program, ss));
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(ss));

    return program;
}
