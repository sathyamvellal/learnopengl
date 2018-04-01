//
// Created by Sathyam Vellal on 09/03/2018.
//

#include <string>
#include <initializer_list>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/logger.h"
#include "utils/files.h"

#include "utils/shader.h"

Shader::Shader(const unsigned int shaderType, const std::string& filename)
        : shaderType(shaderType), filename(filename)
{
    load();
}

Shader::Shader(const Shader& shader)
        : shaderType(shader.shaderType), filename(shader.filename)
{
    load();
}

Shader Shader::operator=(const Shader& shader)
{
    return Shader(*this);
}

Shader::~Shader()
{
    // Nothing to implement here;
    // Shader::destroy() must be called explicitly!
}

unsigned int Shader::getId() const
{
    return this->id;
}

void Shader::use()
{
    // TODO: use shader
}

void Shader::load()
{
    // TODO: load shader

    std::string contents;

    log<LOG_VERBOSE>("loading shader %1% ...") % filename.c_str();

    log<LOG_VERBOSE>("extracting contents ...");
    extract(contents, filename);
    char *contentsCStr = (char *) contents.c_str();

    log<LOG_VERBOSE>("creating shader ...");
    id = glCreateShader(shaderType);
    glShaderSource(id, 1, &contentsCStr, NULL);

    log<LOG_VERBOSE>("compiling shader ...");
    glCompileShader(id);

    if (LOG_LEVEL >= LOG_CRITICAL) {
        int success;
        const int LOGBUF_SIZE = 512;
        char infoLog[LOGBUF_SIZE];

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, LOGBUF_SIZE, NULL, infoLog);
            log<LOG_CRITICAL>("ERROR: failed to compile shader %1%") % filename.c_str();
            log<LOG_CRITICAL>("%1%") % infoLog;
            exit(1);
        } else {
            log<LOG_VERBOSE>("successfuly compiled shader ...");
        }
    }
}

void Shader::destroy()
{
    glDeleteShader(id);
}

ShaderProgram::ShaderProgram()
{
    id = glCreateProgram();
}

ShaderProgram::ShaderProgram(const ShaderProgram& shaderProgram)
        : id(shaderProgram.id) {}

ShaderProgram ShaderProgram::operator=(const ShaderProgram& shaderProgram)
{
    return *this;
}

ShaderProgram::~ShaderProgram()
{
    // Nothing to do here
}

unsigned int ShaderProgram::getId() const
{
    return id;
}

void ShaderProgram::use()
{
    glUseProgram(id);
}

void ShaderProgram::link()
{
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        log<LOG_ERROR>("failed to link shader program ...");
        glfwTerminate();
        exit(1);
    }
}

void ShaderProgram::attachShader(const Shader& shader)
{
    glAttachShader(id, shader.getId());
}

void ShaderProgram::attachShaders(std::initializer_list<Shader> shaders)
{
    for (Shader shader : shaders) {
        attachShader(shader);
    }
}
