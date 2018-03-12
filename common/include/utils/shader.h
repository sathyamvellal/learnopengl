//
// Created by Sathyam Vellal on 09/03/2018.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <string>

class Shader {
public:
    Shader(const unsigned int shaderType, const std::string& filename);
    unsigned int getId();
    void use();
    void destroy();

private:
    const std::string filename;
    const unsigned int shaderType;
    unsigned int id;

    void load();
};

#endif //LEARNOPENGL_SHADER_H
