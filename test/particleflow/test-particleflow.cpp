//
// Created by Sathyam Vellal on 17/03/2018.
//

#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/logger.h"
#include "utils/shader.h"

#include "particleflow/particleflow.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const char *TITLE = "CS520 HW2: Particle Flow";

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void processInput(GLFWwindow *window);

bool lbutton = false;

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
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    Shader vertexShader(GL_VERTEX_SHADER, "shaders/particleflow/vertex.glsl");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/particleflow/fragment.glsl");

    ShaderProgram shaderProgram;
    shaderProgram.attachShaders({vertexShader, fragmentShader});
    shaderProgram.link();
    vertexShader.destroy();
    fragmentShader.destroy();

    init();

    unsigned int VBO, VBO2, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nVertices, vertices1, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nVertices, velocities1, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPointSize(1.0);

    while(!glfwWindowShouldClose(window)) { processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float sineValue = sin(timeValue) / 2.0f;

        step();

        shaderProgram.use();
        int vertexColorLocation = glGetUniformLocation(shaderProgram.getId(), "ourColor");
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nVertices, vertices1, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nVertices, velocities1, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_POINTS, 0, nVertices);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (lbutton) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            o.x = (2 * xpos - WIDTH) / WIDTH;
            o.y = -(2 * ypos - HEIGHT) / HEIGHT;
        }
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

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            lbutton = true;
        } else if (action == GLFW_RELEASE) {
            lbutton = false;
        }
    }
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        step();
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}