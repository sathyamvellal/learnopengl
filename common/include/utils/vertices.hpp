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
    Vertices(int width = 0)
        :_width(width) {
        if (width > 0) {
            _vertices.reserve((std::size_t) _width * _width);
        }
    }

    int size() {
        return (int) _vertices.size() * sizeof(T);
    }

    int length() {
        return (int) _vertices.size();
    }

    int width() {
        return _width;
    }

    T* data() {
        return _vertices.data();
    }

    Vertices<T>& push(T elem) {
        _vertices.push_back(elem);
        return *this;
    }

    T pop() {
        T front = _vertices.front();
        _vertices.pop_back();
        return front;
    }

    T& operator[](unsigned int i) {
        return _vertices[i];
    }

    T get2(unsigned int i, unsigned int j) {
        return _vertices[i * _width + j];
    }

    void set2(unsigned int i, unsigned int j, T value) {
        _vertices[i * _width + j] = value;
    }
public:
    std::vector<T> _vertices;
    int _width;
};

#endif //LEARNOPENGL_VERTICES_H
