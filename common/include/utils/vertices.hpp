//
// Created by Sathyam Vellal on 18/04/2018.
//

#ifndef LEARNOPENGL_VERTICES_H
#define LEARNOPENGL_VERTICES_H

#include <vector>
#include <glm/glm.hpp>

template <class T>
class Vertices {
public:
    std::size_t size() {
        return _vertices.size() * 4 * sizeof(T);
    }

    T* data() {
        return _vertices.data();
    }

    Vertices<T>& push(glm::tvec4<T> v) {
        _vertices.push_back(v);
        return *this;
    }

    glm::tvec4<T> pop() {
        glm::tvec4<T> front = _vertices.front();
        _vertices.pop_back();
        return front;
    }

    glm::tvec4<T>& operator[](unsigned int i) {
        return _vertices[i];
    }
public:
    std::vector<glm::tvec4<T>> _vertices;

};

#endif //LEARNOPENGL_VERTICES_H
