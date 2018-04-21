//
// Created by Sathyam Vellal on 18/04/2018.
//

#ifndef LEARNOPENGL_GRID_OVERLAY_HPP
#define LEARNOPENGL_GRID_OVERLAY_HPP

#include <cmath>
#include <cstdlib>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common/include/utils/random.h"
#include "common/include/utils/shader.h"
#include "common/include/utils/vertices.hpp"
#include "common/include/utils/shapes/circle.hpp"
#include "common/include/utils/shapes/grid.hpp"

const unsigned int GRID_OVERLAY_RES = GRID_RES;

template <typename T>
struct GridOverlayVertexPositionColour {
    glm::tvec4<T> position;
    glm::tvec4<T> colour;

    GridOverlayVertexPositionColour(glm::tvec4<T> position, glm::tvec4<T> colour)
            :position(position), colour(colour) {}
};

template <typename T>
struct GridOverlayVertexPositionColourSize {
    static const int position = sizeof(GridOverlayVertexPositionColour<T>::position);
    static const int colour = sizeof(GridOverlayVertexPositionColour<T>::colour);
};

template <typename T>
struct GridOverlayVertexPositionColourOffset {
    static const int position = 0;
    static const int colour = GridOverlayVertexPositionColourSize<T>::position;
};

template <class T>
class GridOverlay {
    using GridContainer = GridOverlayVertexPositionColour<T>;
public:
    GridOverlay(Grid<T> &grid, unsigned int res = GRID_OVERLAY_RES)
        :grid(grid), res(res), _width(res) {
        vertices._vertices.reserve(_width * _width * _width * _width);
    }

    void make() {
        double dx = 2.0 / _width;
        double dy = 2.0 / _width;

        double y = 1.0;
        for (int j = 0; j < _width; ++j) {
            double x = -1.0;
            for (int i = 0; i < _width; ++i) {
#if 0
                    vertices.push(GridContainer(glm::tvec4<T>(x, y, 0.0, 1.0), glm::tvec4<T>(1.0, 1.0, 1.0, 1.0)));
                    vertices.push(GridContainer(glm::tvec4<T>(x + dx, y, 0.0, 1.0), glm::tvec4<T>(1.0, 1.0, 1.0, 1.0)));
                    vertices.push(GridContainer(glm::tvec4<T>(x + dx, y - dy, 0.0, 1.0), glm::tvec4<T>(1.0, 1.0, 1.0, 1.0)));
                    vertices.push(GridContainer(glm::tvec4<T>(x, y - dy, 0.0, 1.0), glm::tvec4<T>(1.0, 1.0, 1.0, 1.0)));
#endif
                processCell(i, j, x, y, dx, dy);
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

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }

    void draw() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        shaderProgram->use();

        glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 4, GL_DOUBLE, GL_FALSE, sizeof(GridContainer), (void*)(GridOverlayVertexPositionColourOffset<T>::position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, sizeof(GridContainer), (void*)(GridOverlayVertexPositionColourOffset<T>::colour));
        glEnableVertexAttribArray(1);

        for (int i = 0; i < vertices.length(); i += 2) {
            glDrawArrays(GL_LINES, i, 2);
        }
    }

    void step() {
        remake();
    }

    void processCell(int i, int j, double x, double y, double dx, double dy) {
        const std::string ONE = "1";
        const std::string ZERO = "0";
        const double dx2 = dx / 2;
        const double dy2 = dx / 2;

#define THRESHOLD(I, J) (grid.iso.get2((I), (J)) > 0.05 ? ONE : ZERO)

        std::string type = THRESHOLD(i, j)
                           + THRESHOLD(i + 1, j)
                           + THRESHOLD(i + 1, j + 1)
                           + THRESHOLD(i, j + 1);

        const double LERPXN = lerp(i, j, i + 1, j, dx);
        const double LERPXS = lerp(i, j + 1, i + 1, j + 1, dx);
        const double LERPYW = lerp(i, j, i, j + 1, dy);
        const double LERPYE = lerp(i + 1, j, i + 1, j + 1, dy);

        if (type == "1000") {
            push(x, y - LERPYW);
            push(x + LERPXN, y);
        } else if (type == "0100") {
            push(x + LERPXN, y); //push(x + dx2, y);
            push(x + dx, y - LERPYE); //push(x + dx, y - dy2);
        } else if (type == "0010") {
            push(x + dx, y - LERPYE); //push(x + dx, y - dy2);
            push(x + LERPXS, y - dy); //push(x + dx2, y - dy);
        } else if (type == "0001") {
            push(x + LERPXS, y - dy);
            push(x, y - LERPYW);
        } else if (type == "1001") {
            push(x + LERPXN, y);
            push(x + LERPXS, y - dy);
        } else if (type == "1100") {
            push(x, y - LERPYW); //push(x, y - dy2);
            push(x + dx, y - LERPYE); //push(x + dx, y - dy2);
        } else if (type == "0110") {
            push(x + LERPXN, y);
            push(x + LERPXS, y - dy);
        } else if (type == "0011") {
            push(x, y - LERPYW);
            push(x + dx, y - LERPYE);
        } else if (type == "1110") {
            push(x, y - LERPYW);
            push(x + LERPXS, y - dy);
        } else if (type == "0111") {
            push(x, y - LERPYW);
            push(x + LERPXN, y);
        } else if (type == "1011") {
            push(x + LERPXN, y);
            push(x + dx, y - LERPYE);
        } else if (type == "1101") {
            push(x + dx, y - LERPYE);
            push(x + LERPXS, y - dy);
        } else if (type == "0101") {
            push(x + LERPXN, y);
            push(x + dx, y - LERPYE);
            push(x, y - LERPYW);
            push(x + LERPXS, y - dy);
        } else if (type == "1010") {
            push(x, y - LERPYW);
            push(x + LERPXN, y);
            push(x + dx, y - LERPYE);
            push(x + LERPXS, y - dy);
        }
    }

#if 0
    double lerpx(int i, int j, double x, double dx) {
        double a = grid.iso.get2(i, j);
        double b = grid.iso.get2(i + 1, j);
        return lerp(a, b);
    }

    double lerpy(int i, int j, double y, double dy) {
        double a = grid.iso.get2(i, j);
        double b = grid.iso.get2(i, j + 1);
        return lerp(a, b);
    }
#endif

    double lerp(int ai, int aj, int bi, int bj, double v) {
        double a = grid.iso.get2(ai, aj);
        double b = grid.iso.get2(bi, bj);
        return (a - b) / 2 * v;
    }

    void push(double x, double y) {
        static const glm::tvec4<T> lineColour(1.0, 1.0, 0.0, 1.0);
        vertices.push(GridContainer(glm::tvec4<T>((x), (y), 0.0, 1.0), lineColour));
    }
public:
    Vertices<GridContainer> vertices;
    unsigned int res;
    unsigned int _width;

    unsigned int VAO, VBO;
    ShaderProgram *shaderProgram;

    Grid<T> &grid;
};

#endif //LEARNOPENGL_GRID_OVERLAY_HPP
