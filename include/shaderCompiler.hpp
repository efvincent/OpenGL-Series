#pragma once

#include <string>

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

/**
 * @brief Accept a file path to a combined vertex/frag shader program, and
 * return the source code parsed into the `ShaderProgramSource` struct 
 * 
 * @param filepath path to the source code 
 * @return ShaderProgramSource parsed struct
 */
ShaderProgramSource parseShader(const std::string& filepath);

unsigned int compileShaderProgram(unsigned int type, const std::string& source);

unsigned int createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
