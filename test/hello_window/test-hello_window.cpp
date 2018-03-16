//
// Created by Sathyam Vellal on 01/03/2018.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/logger.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "LearnOpenGL: Hello Window";

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

    log<LOG_VERBOSE>("setting viewport ...");
    glViewport(0, 0, WIDTH, HEIGHT);

    log<LOG_VERBOSE>("setting resize callback");
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    log<LOG_INFO>("successfully initialised GLFW ...");
    log<LOG_INFO>("successfully initialised GLAD ...");
    log<LOG_INFO>("starting main loop ...");
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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