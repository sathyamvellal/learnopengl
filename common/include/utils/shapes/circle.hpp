//
// Created by Sathyam Vellal on 18/04/2018.
//

#ifndef LEARNOPENGL_SHAPES_HPP
#define LEARNOPENGL_SHAPES_HPP

#include <cmath>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "common/include/utils/random.h"
#include "common/include/utils/shader.h"
#include "common/include/utils/vertices.hpp"

const unsigned int CIRCLE_DEFAULT_RES = 32;

template <typename T>
struct CircleVertexPositionColour {
    glm::tvec4<T> position;
    glm::tvec4<T> colour;

    CircleVertexPositionColour(glm::tvec4<T> position, glm::tvec4<T> colour)
            :position(position), colour(colour) {}
};

template <typename T>
struct CircleVertexPositionColourSize {
    static const int position = sizeof(CircleVertexPositionColour<T>::position);
    static const int colour = sizeof(CircleVertexPositionColour<T>::colour);
};

template <typename T>
struct CircleVertexPositionColourOffset {
    static const int position = 0;
    static const int colour = CircleVertexPositionColourSize<T>::position;
};

template <typename T>
struct CircleVertexPosition {
    glm::tvec4<T> position;

    CircleVertexPosition(glm::tvec4<T> position)
            :position(position) {}
};

template <class T>
class Circle {
    using CircleContainer = CircleVertexPositionColour<T>;
public:
    Circle<T>(glm::tvec4<T> center, T radius, unsigned int res = CIRCLE_DEFAULT_RES)
            :center(center), radius(radius), res(res), theta(2 * M_PI / res), shaderProgram(0) {
        vertices._vertices.reserve(res+1);
        if (fabs(center.x) > (1.0 - radius)) this->center.x = (center.x > 0 ? 0.25 : -0.25);
        if (fabs(center.y) > (1.0 - radius)) this->center.y = (center.y > 0 ? 0.25 : -0.25);
        make();
    }

    void make() {
        for (int i = 0; i <= res; ++i) {
            vertices.push(CircleContainer(
                    glm::tvec4<T>(center.x - std::cos(i * theta) * radius,
                                  center.y - std::sin(i * theta) * radius,
                                  0.0f,
                                  1.0f),
                    glm::tvec4<T>(0.0, 1.0, 0.0, 1.0)
            ));
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

        dir.x = dir.y = dir.z = dir.w = 1;
        dir.x *= drand() > 0.5 ? 1 : -1;
        dir.y *= drand() > 0.5 ? 1 : -1;

        vdt.x = drand() / 100.0;
        vdt.y = drand() / 100.0;
    }

    void draw() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        shaderProgram->use();

        glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 4, GL_DOUBLE, GL_FALSE, sizeof(CircleContainer), (void*)(CircleVertexPositionColourOffset<T>::position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, sizeof(CircleContainer), (void*)(CircleVertexPositionColourOffset<T>::colour));
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_LINE_STRIP, 0, vertices.length());
    }

    void step() {
        center.x += vdt.x * dir.x;
        center.y += vdt.y * dir.y;
        remake();

        if (fabs(center.x) > (1.0 - radius)) dir.x *= -1;
        if (fabs(center.y) > (1.0 - radius)) dir.y *= -1;
    }
public:
    Vertices<CircleContainer> vertices;
    T theta;
    T radius;
    glm::tvec4<T> center;
    unsigned int res;

    glm::ivec4 dir;
    glm::dvec4 vdt;

    unsigned int VAO, VBO;
    ShaderProgram *shaderProgram;
};

#endif //LEARNOPENGL_SHAPES_HPP
