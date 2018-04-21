//
// Created by Sathyam Vellal on 18/04/2018.
//

#ifndef LEARNOPENGL_GRID_HPP
#define LEARNOPENGL_GRID_HPP

#include <cmath>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common/include/utils/logger.h"
#include "common/include/utils/random.h"
#include "common/include/utils/shader.h"
#include "common/include/utils/vertices.hpp"
#include "common/include/utils/shapes/circle.hpp"

const unsigned int GRID_RES = 256;

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
    Grid(std::vector<Circle<T>> &circles, unsigned int res = GRID_RES)
        :circles(circles), res(res), _width(res + 1), vertices(res), iso(res) {
#if 1
        for (int i = 0; i < _width; ++i) {
            for (int j = 0; j < _width; ++j) {
                iso.push(0.0);
            }
        }
#endif
        make();
    }

    GridContainer& operator()(int i, int j) {
        return vertices[i * _width + j];
    }

    void make() {
        double dx = 2.0 / res;
        double dy = 2.0 / res;

        double y = 1.0;
        for (int j = 0; j < _width; ++j) {
            double x = -1.0;
            for (int i = 0; i < _width; ++i) {
                double val = 0.0;
                for (int k = 0; k < circles.size(); ++k) {
                    val += isovalue(x, y, circles[k]);
                }
                iso.set2(i, j, val);
#if 0
                vertices.push(GridContainer(
                        glm::tvec4<T>(x,   y,   0.0, 1.0),
                        glm::tvec4<T>(1.0, (iso.get2(i, j) > 1.0 ? 0.0 : 1.0), (iso.get2(i, j) > 1.0 ? 0.0 : 1.0), 1.0)
                ));
#endif
                x += dx;
            }
            y -= dy;
        }
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

    double isovalue(double x, double y, Circle<T> &circle) {
        double dx = x - circle.center.x;
        double dy = y - circle.center.y;
        double d2 = dx * dx + dy * dy;
        return circle.radius * circle.radius / d2;
    }
public:
    Vertices<GridContainer> vertices;
    Vertices<double> iso;
    unsigned int res;
    unsigned int _width;

    unsigned int VAO, VBO;
    ShaderProgram *shaderProgram;

    std::vector<Circle<double>> &circles;
};

#endif //LEARNOPENGL_GRID_HPP
