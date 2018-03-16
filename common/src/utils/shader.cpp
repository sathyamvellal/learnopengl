//
// Created by Sathyam Vellal on 09/03/2018.
//

#include <string>

#include <glad/glad.h>

#include "utils/logger.h"
#include "utils/files.h"

#include "utils/shader.h"

Shader::Shader(const unsigned int shaderType, const std::string& filename)
        : shaderType(shaderType), filename(filename)
{
    load();
}

unsigned int Shader::getId()
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
