//
// Created by Sathyam Vellal on 18/04/2018.
//

#ifndef LEARNOPENGL_SHAPES_HPP
#define LEARNOPENGL_SHAPES_HPP

#include <cmath>
#include "common/include/utils/vertices.hpp"

const unsigned int CIRCLE_DEFAULT_RES = 32;

template <class T>
class Circle {
public:
    Circle<T>(glm::tvec4<T> center, T radius, unsigned int res = CIRCLE_DEFAULT_RES)
            :center(center), radius(radius), res(res), theta(2 * M_PI / res) {
        vertices._vertices.reserve(res);
        make();
    }

    void make() {
        for (int i = 0; i <= res; ++i) {
            vertices.push(glm::tvec4<T>(center.x - std::cos(i * theta) * radius,
                                        center.y - std::sin(i * theta) * radius,
                                        0.0f,
                                        1.0f)
            );
        }
    }

    void remake() {
        vertices._vertices.clear();
        make();
    }
public:
    Vertices<T> vertices;
    T theta;
    T radius;
    glm::tvec4<T> center;
    unsigned int res;
};

#endif //LEARNOPENGL_SHAPES_HPP
