//
// Created by apple on 2022/9/15.
//

#include "shader.h"
#include <fstream>
#include <sstream>
#include <glad/glad.h>

shader::shader(const char *vertexPath, const char *fragmentPath) : ID(0)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vIfs;
    std::ifstream fIfs;
    vIfs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fIfs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vIfs.open(vertexPath);
        fIfs.open(fragmentPath);
        std::stringstream vFileStream, fFileStream;
        vFileStream << vIfs.rdbuf();
        fFileStream << fIfs.rdbuf();
        vIfs.close();
        fIfs.close();

        vertexCode = vFileStream.str();
        fragmentCode = fFileStream.str();
    } catch (std::ifstream::failure)
    {

    }
    unsigned int vertexShader = initShader(vertexCode.c_str(), GL_VERTEX_SHADER);
    if (vertexShader <= 0)
        return;
    unsigned int fragmentShader = initShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);
    if (fragmentShader <= 0)
        return;
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    if (checkCompileErrors(ID, "PROGRAM"))
        glDeleteProgram(ID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void shader::use()
{
    if (ID > 0)
        glUseProgram(ID);
}

unsigned int shader::initShader(const char *code, unsigned int type)
{
    unsigned int shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    if (checkCompileErrors(shader, "SHADER"))
        glDeleteShader(shader);
    return shader;
}

bool shader::checkCompileErrors(unsigned int shader, const std::string type)
{
    int success;
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[1024];
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[1024];
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    return !success;
}
