//
// Created by Sathyam Vellal on 18/04/2018.
//

#ifndef LEARNOPENGL_GRID_HPP
#define LEARNOPENGL_GRID_HPP

#include <cmath>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common/include/utils/random.h"
#include "common/include/utils/shader.h"
#include "common/include/utils/vertices.hpp"

const unsigned int GRID_DEFAULT_RES = 16;

template <typename T>
struct GridVertexPositionColour {
    glm::tvec4<T> position;
    glm::tvec4<T> colour;

    GridVertexPositionColour(glm::tvec4<T> position, glm::tvec4<T> colour)
            :position(position), colour(colour) {}
};

template <typename T>
struct GridVertexPositionColourSize {
    static const int position = sizeof(GridVertexPositionColour<T>::position);
    static const int colour = sizeof(GridVertexPositionColour<T>::colour);
};

template <typename T>
struct GridVertexPositionColourOffset {
    static const int position = 0;
    static const int colour = GridVertexPositionColourSize<T>::position;
};

template <typename T>
struct GridVertexPosition {
    glm::tvec4<T> position;

    GridVertexPosition(glm::tvec4<T> position)
            :position(position) {}
};

template <class T>
class Grid {
    using GridContainer = GridVertexPositionColour<T>;
//    using GridContainer = GridVertexPosition<T>;
public:
    Grid(unsigned int res = GRID_DEFAULT_RES)
        :res(res) {
        vertices._vertices.reserve((res + 1) * (res + 1));
        make();
    }

    void make() {
#if 1
        double dx = 2.0 / res;
        double dy = 2.0 / res;

        int count = 0;
        for (double i = -1.0; i <= 1.0; i += dx) {
            for (double j = -1.0; j <= 1.0; j += dy) {
                vertices.push(GridContainer(
                        glm::tvec4<T>(i,   j,   0.0, 1.0),
                        glm::tvec4<T>(1.0, 0.3, 1.0, 1.0)
                ));
            }
        }
#endif
    }

    void remake() {
        vertices._vertices.clear();
        make();
    }

    void drawInit(ShaderProgram &shaderProgram) {
        this->shaderProgram = &shaderProgram;

        glPointSize(5.0);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }

    void draw() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        shaderProgram->use();

        glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 4, GL_DOUBLE, GL_FALSE, sizeof(GridContainer), (void*)(GridVertexPositionColourOffset<T>::position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, sizeof(GridContainer), (void*)(GridVertexPositionColourOffset<T>::colour));
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_POINTS, 0, vertices.length());
    }

    void step() {
        remake();
    }
public:
    Vertices<GridContainer> vertices;
    unsigned int res;

    unsigned int VAO, VBO;
    ShaderProgram *shaderProgram;
};

#endif //LEARNOPENGL_GRID_HPP
