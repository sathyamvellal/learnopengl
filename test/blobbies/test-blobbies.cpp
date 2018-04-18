//
// Created by Sathyam Vellal on 17/04/2018.
//

#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/logger.h"
#include "utils/shader.h"

#include "blobbies/blobbies.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const char *TITLE = "CS520 HW3: Blobbies";

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

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

    while(!glfwWindowShouldClose(window)) { processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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