//
// Created by Sathyam Vellal on 18/04/2018.
//

#ifndef LEARNOPENGL_SHAPES_HPP
#define LEARNOPENGL_SHAPES_HPP

#include <cmath>
#include "vertices.hpp"

template <class T>
class Circle {
public:
    Circle<T>(T radius, unsigned int res = 32)
            :radius(radius), res(res), theta(2 * M_PI / res) {
        make();
    }

    void make() {
        for (int i = 0; i < res; ++i) {
            vertices.push(glm::tvec4<T>(std::cos(i * theta) * radius, std::sin(i * theta) * radius, 0.0, 1.0));
        }
    }
public:
    Vertices<T> vertices;
    T theta;
    T radius;
    unsigned int res;
};

#endif //LEARNOPENGL_SHAPES_HPP
