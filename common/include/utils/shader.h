//
// Created by Sathyam Vellal on 09/03/2018.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <string>
#include <initializer_list>

class Shader {
public:
    Shader(const unsigned int shaderType, const std::string& filename);
    Shader(const Shader& shader);
    Shader operator=(const Shader& shader);
    ~Shader();

    unsigned int getId() const;
    void use();
    void destroy();

private:
    const std::string filename;
    const unsigned int shaderType;
    unsigned int id;

    void load();
};

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(const ShaderProgram& shaderProgram);
    ShaderProgram operator=(const ShaderProgram& shaderProgram);
    ~ShaderProgram();

    unsigned int getId() const;
    void use();
    void link();

    void attachShader(const Shader& shader);
    void attachShaders(std::initializer_list<Shader> shaders);

private:
    unsigned int id;
};

#endif //LEARNOPENGL_SHADER_H
