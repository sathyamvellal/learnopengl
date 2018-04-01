//
// Created by Sathyam Vellal on 17/03/2018.
//

#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/logger.h"
#include "utils/shader.h"

#include "spring1d/spring1d.h"
#include "spring1d/spring1dsim.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const char *TITLE = "Spring1D Simulation";

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

float vertices2[2][3] = {
        { -0.5f,  0.0f,  0.0f },
        {  0.5f,  0.0f,  0.0f }
};

float *vertices1 = &vertices2[0][0];
Spring1DSim *ptrSpring1DSim = 0;

int main(int argc, char **argv)
{
#if 1
    Spring1DSim spring1DSim(Spring1D(10.0));
    ptrSpring1DSim = &spring1DSim;

    spring1DSim.attachMass(1.0);
    spring1DSim.setRestLength(10.0);

    spring1DSim.init();
    // spring1DSim.fField = 20;

#endif

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

    Shader vertexShader(GL_VERTEX_SHADER, "shaders/spring1d/vertex.glsl");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/spring1d/fragment.glsl");

    ShaderProgram shaderProgram;
    shaderProgram.attachShaders({vertexShader, fragmentShader});
    shaderProgram.link();
    vertexShader.destroy();
    fragmentShader.destroy();

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 2, vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vertices2[1][0] = spring1DSim.x0 / 20;

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float sineValue = sin(timeValue) / 2.0f;

        shaderProgram.use();
        int vertexColorLocation = glGetUniformLocation(shaderProgram.getId(), "ourColor");
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);

        spring1DSim.step();
        //spring1DSim.step();
        vertices2[1][0] = spring1DSim.x / 20;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 2, vertices1, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_LINES, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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
        ptrSpring1DSim->fInst = 200.0;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}