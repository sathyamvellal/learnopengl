//
// Created by Sathyam Vellal on 07/03/2018.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/logger.h"
#include "utils/shader.h"

#include "hello_triangle/hello_triangle.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "LearnOpenGL: Hello Triangle";

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(int argc, char** argv)
{
    GLFWwindow* window;

    log<LOG_VERBOSE>("enter main ...");
    log<LOG_VERBOSE>("initializing GLFW ...");
    if (!glfwInit()) {
        log<LOG_ERROR>("failed to initialise GLFW ...");
        exit(1);
    }
    log<LOG_VERBOSE>("setting context version major ...");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    log<LOG_VERBOSE>("setting context version minior ...");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    log<LOG_VERBOSE>("setting use core profile ...");
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    log<LOG_VERBOSE>("enabling forward compatibility ...");
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    log<LOG_VERBOSE>("creating window ...");
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (!window) {
        log<LOG_ERROR>("failed creating window ...");
        glfwTerminate();
        exit(1);
    }
    log<LOG_VERBOSE>("setting main context as window ...");
    glfwMakeContextCurrent(window);

    log<LOG_VERBOSE>("initialising GLAD ...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log<LOG_ERROR>("failed to initialise GLAD ...");
        exit(1);
    }

    log<LOG_VERBOSE>("setting resize callback");
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    log<LOG_INFO>("successfully initialised GLFW ...");
    log<LOG_INFO>("successfully initialised GLAD ...");

    log<LOG_VERBOSE>("creating vertex shader ...");
    Shader vertexShader(GL_VERTEX_SHADER, "/Users/sathyam/repos/gh/learnopengl/build/shaders/hello_triangle/vertex.glsl");
    log<LOG_VERBOSE>("creating fragment shader ...");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "/Users/sathyam/repos/gh/learnopengl/build/shaders/hello_triangle/fragment.glsl");

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.getId());
    glAttachShader(shaderProgram, fragmentShader.getId());
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        log<LOG_CRITICAL>("ERROR: Error in linking program ...");
        exit(1);
    }
    vertexShader.destroy();
    fragmentShader.destroy();

    log<LOG_VERBOSE>("setting up VAO and VBO ...");
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    log<LOG_VERBOSE>("binding VAO ...");
    glBindVertexArray(VAO);

    log<LOG_VERBOSE>("binding VBO ...");
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    log<LOG_VERBOSE>("vertex data to VBO...");
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 6, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0));
    glEnableVertexAttribArray(0);

    log<LOG_VERBOSE>("unbinding VBO ...");
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    log<LOG_VERBOSE>("unbinding VAO ...");
    glBindVertexArray(0);

    log<LOG_INFO>("starting main loop ...");
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}