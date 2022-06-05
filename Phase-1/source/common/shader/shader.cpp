#include "shader.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

void our::ShaderProgram::create()
{
    // Create Shader Program
    program = glCreateProgram();
}

void our::ShaderProgram::destroy()
{
    // Delete Shader Program
    if (program != 0)
        glDeleteProgram(program);
    program = 0;
}

// Forward definition for error checking functions
std::string checkForShaderCompilationErrors(GLuint shader);
std::string checkForLinkingErrors(GLuint program);

bool our::ShaderProgram::attach(const std::string &filename, GLenum type) const
{
    // Here, we open the file and read a string from it containing the GLSL code of our shader
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "ERROR: Couldn't open shader file: " << filename << std::endl;
        return false;
    }
    std::string sourceString = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    const char *sourceCStr = sourceString.c_str();
    file.close();

    GLuint shaderID = glCreateShader(type);

    // ================ < --- Compile Shader --- > ================ //

    // TODO: send the source code to the shader and compile it

    //==// shaderID:   Shader That we want to Set its source code
    //==// 1:          #strings --> (Source Codes) <-- and We have Just One
    //==// sourceCStr: String That Contain Shader Code
    //==// nullptr:    Means That The String of The Src Code is NULL Terminated
    glShaderSource(shaderID, 1, &sourceCStr, nullptr);   

    // Compile shader Of Given ID
    glCompileShader(shaderID);

    // Here we check for compilation errors

    // ================ < --- End --- > ================ //


    // ================ < --- Attach Program --- > ================ //

    // TODO: Uncomment this if block
    if (std::string error = checkForShaderCompilationErrors(shaderID); error.size() != 0)
    {
        std::cerr << "ERROR IN " << filename << std::endl;
        std::cerr << error << std::endl;
        glDeleteShader(shaderID);
        return false;
    }

    // TODO: attach the shader to the program then delete the shader
    //==//  Attach the shader to the program to link everything together
    glAttachShader(program, shaderID);

    //==// We don't need this shader anymore, it has been already attached to the program object
    glDeleteShader(shaderID);

    // ================ < --- End --- > ================ //

    // We return true since the compilation succeeded
    return true;
}

bool our::ShaderProgram::link() const
{

    // ================ < --- Link Program --- > ================ //

    // TODO: call opengl to link the program identified by this->program
    
    //==// Link Program & Attached shader will Be Used To Create Executables.
    glLinkProgram(program);

    // Here we check for linking errors
    // TODO: Uncomment this if block
    if(auto error = checkForLinkingErrors(program); error.size() != 0){
        std::cerr << "LINKING ERROR" << std::endl;
        std::cerr << error << std::endl;
        return false;
    }

    // ================ < --- End --- > ================ //

    return true;
}

////////////////////////////////////////////////////////////////////
// Function to check for compilation and linking error in shaders //
////////////////////////////////////////////////////////////////////

std::string checkForShaderCompilationErrors(GLuint shader)
{
    // Check and return any error in the compilation process
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *logStr = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, logStr);
        std::string errorLog(logStr);
        delete[] logStr;
        return errorLog;
    }
    return std::string();
}

std::string checkForLinkingErrors(GLuint program)
{
    // Check and return any error in the linking process
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *logStr = new char[length];
        glGetProgramInfoLog(program, length, nullptr, logStr);
        std::string error(logStr);
        delete[] logStr;
        return error;
    }
    return std::string();
}