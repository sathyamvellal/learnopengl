//
// Created by Sathyam Vellal on 18/04/2018.
//

#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "utils/logger.h"
#include "utils/random.h"
#include "utils/shader.h"
#include "utils/shapes/circle.hpp"
#include "utils/shapes/grid.hpp"
#include "utils/shapes/grid-overlay.hpp"

#include "sandbox001/sandbox001.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;
const char *TITLE = "Sandbox 001";
bool paused = false;

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

    Shader vertexShader(GL_VERTEX_SHADER, "shaders/sandbox001/vertex.glsl");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/sandbox001/fragment.glsl");

    ShaderProgram shaderProgram;
    shaderProgram.attachShaders({vertexShader, fragmentShader});
    shaderProgram.link();
    vertexShader.destroy();
    fragmentShader.destroy();

    std::vector<Circle<double>> circles;
    int nCircles = 5;
    Grid<double> grid(circles);
    GridOverlay<double> gridOverlay(grid);

    for (int i = 0; i < nCircles; ++i) {
        circles.emplace_back(Circle<double>(glm::tvec4<double>(signdrand(), signdrand(), 0.0, 1.0), 0.2 * drand()));
        circles[i].make();
        circles[i].drawInit(shaderProgram);
    }
    grid.make();
    grid.drawInit(shaderProgram);
    gridOverlay.make();
    gridOverlay.drawInit(shaderProgram);

    while(!glfwWindowShouldClose(window)) { processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!paused) {
            for (int i = 0; i < nCircles; ++i) {
                circles[i].step();
            }
            grid.step();
            gridOverlay.step();
        }

        for (int i = 0; i < nCircles; ++i) {
            circles[i].draw();
        }
        grid.draw();
        gridOverlay.draw();

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
        paused = !paused;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void draw()
{
}