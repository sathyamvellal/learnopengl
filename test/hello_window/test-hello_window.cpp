//
// Created by Sathyam Vellal on 01/03/2018.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utils/logger.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "LearnOpenGL: Hello Window";

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(int argc, char** argv)
{
    GLFWwindow* window;

    log<LOG_VERBOSE>(L"enter main ...");
    log<LOG_VERBOSE>(L"initializing GLFW ...");
    if (!glfwInit()) {
        log<LOG_ERROR>(L"failed to initialise GLFW ...");
        exit(1);
    }
    log<LOG_VERBOSE>(L"setting context version major ...");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    log<LOG_VERBOSE>(L"setting context version minior ...");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    log<LOG_VERBOSE>(L"setting use core profile ...");
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    log<LOG_VERBOSE>(L"enabling forward compatibility ...");
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    log<LOG_VERBOSE>(L"creating window ...");
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (!window) {
        log<LOG_ERROR>(L"failed creating window ...");
        glfwTerminate();
        exit(1);
    }
    log<LOG_VERBOSE>(L"setting main context as window ...");
    glfwMakeContextCurrent(window);

    log<LOG_VERBOSE>(L"initialising GLAD ...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log<LOG_ERROR>(L"failed to initialise GLAD ...");
        exit(1);
    }

    log<LOG_VERBOSE>(L"setting viewport ...");
    glViewport(0, 0, WIDTH, HEIGHT);

    log<LOG_VERBOSE>(L"setting resize callback");
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    log<LOG_INFO>(L"successfully initialised GLFW ...");
    log<LOG_INFO>(L"successfully initialised GLAD ...");
    log<LOG_INFO>(L"starting main loop ...");
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

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