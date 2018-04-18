//
// Created by Sathyam Vellal on 19/03/2018.
//

#include <cmath>

#include <glm/glm.hpp>

#include "utils/logger.h"

#include "spring2d/spring2d.h"
#include "spring2d/spring2dsim.h"

int main(int argc, char **argv)
{
    Spring2DSim spring2DSim(Spring2DSim(5.0));

    spring2DSim.init();

    glm::vec2 a(2, 3);
    glm::vec2 b(1, 7);
    glm::vec2 ub = b / glm::length(b);
    glm::vec2 proja_b = glm::dot(a, ub) * ub;

    std::cout << proja_b.x << std::endl;
    std::cout << proja_b.y << std::endl;

    std::cout << glm::length(proja_b) << std::endl;

    return 0;
}