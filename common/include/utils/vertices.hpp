//
// Created by Sathyam Vellal on 18/04/2018.
//

#ifndef LEARNOPENGL_VERTICES_H
#define LEARNOPENGL_VERTICES_H

#include <vector>
#include <glm/glm.hpp>

#define VERTICES_OLD 0

template <class T>
class Vertices {
public:
#if VERTICES_OLD
    int size() {
        return (int) _vertices.size() * 4 * sizeof(T);
    }
#else
    int size() {
        return (int) _vertices.size() * sizeof(T);
    }
#endif

    int length() {
        return (int) _vertices.size();
    }

    T* data() {
        return _vertices.data();
    }

#if VERTICES_OLD
    Vertices<T>& push(glm::tvec4<T> v) {
        _vertices.emplace_back(v);
        return *this;
    }
#else
    Vertices<T>& push(T elem) {
        _vertices.emplace_back(elem);
        return *this;
    }
#endif

#if VERTICES_OLD
    glm::tvec4<T> pop() {
        glm::tvec4<T> front = _vertices.front();
        _vertices.pop_back();
        return front;
    }
#else
    T pop() {
        T front = _vertices.front();
        _vertices.pop_back();
        return front;
    }
#endif

#if VERTICES_OLD
    glm::tvec4<T>& operator[](unsigned int i) {
        return _vertices[i];
    }
#else
    T operator[](unsigned int i) {
        return _vertices[i];
    }
#endif
public:
#if VERTICES_OLD
    std::vector<glm::tvec4<T>> _vertices;
#else
    std::vector<T> _vertices;
#endif
};

#endif //LEARNOPENGL_VERTICES_H
