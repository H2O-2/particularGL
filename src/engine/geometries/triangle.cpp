#include "triangle.hpp"

// Triangle::Triangle() : Geometry(), angleOne(60.0f), angleTwo(60.0f) {
//     posns.resize(3);
// }

Triangle::Triangle(float angleOne, float angleTwo) : Geometry(), angleOne(angleOne), angleTwo(angleTwo) {
    posns.reserve(3);
}

void Triangle::init() {
    // posns.emplace_back(glm::vec3(-0.5f, -0.5f, 0.0f));
    // posns.emplace_back(glm::vec3(0.5f, -0.5f, 0.0f));
    // posns.emplace_back(glm::vec3(0.0f,  0.5f, 0.0f));

    posns.emplace_back(glm::vec3(-0.5f, -0.5f, 0.0f));
    posns.emplace_back(glm::vec3(0.5f, -0.5f, 0.0f));
    posns.emplace_back(glm::vec3(0.0f,  0.5f, 0.0f));

    bufferGeometry();
}
