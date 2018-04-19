//
// Created by Sathyam Vellal on 18/04/2018.
//

#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/logger.h"
#include "utils/shader.h"
#include "utils/shapes.hpp"

#include "sandbox001/sandbox001.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;
const char *TITLE = "Sandbox 001";

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

void draw();

int main(int argc, char **argv)
{
    GLFWwindow *window;

    if (!glfwInit()) {
        log<LOG_ERROR>("failed to initialise GLFW ...");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (!window) {
        log<LOG_ERROR>("Failed to create window ...");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log<LOG_ERROR>("Failed to initialise GLAD");
        glfwTerminate();
        exit(1);
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    Shader vertexShader(GL_VERTEX_SHADER, "shaders/blobbies/vertex.glsl");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/blobbies/fragment.glsl");

    ShaderProgram shaderProgram;
    shaderProgram.attachShaders({vertexShader, fragmentShader});
    shaderProgram.link();
    vertexShader.destroy();
    fragmentShader.destroy();

    Circle<float> circle(0.5f);
    circle.make();

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, circle.vertices.size(), &circle.vertices[0].x, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(window)) { processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int vertexColorLocation = glGetUniformLocation(shaderProgram.getId(), "ourColor");

        shaderProgram.use();
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, circle.vertices.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void draw()
{
}