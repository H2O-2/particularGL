#include "square.hpp"

float DEFAULT_ASPECT = 1.0f;
float SQUARE_INDEX = 6;
float SQUARE_BASE_SCALE = 2.0f;

Square::Square(float aspectRatio) : Geometry(SQUARE_INDEX, SQUARE_BASE_SCALE, GL_TRIANGLES), aspectRatio(aspectRatio) {
    posns.reserve(indexNum);
    indices.reserve(6);
}

void Square::init() {
    initSquareVertices();

    indices = {
        0, 2, 1,
        0, 3, 2
    };

    // Write to GPU
    bufferGeometry();
}

int Square::getIndexNum() const {
    return indexNum;
}

void Square::setAspectRatio(const float r) {
    if (r != aspectRatio) {
        aspectRatio = r;
        initSquareVertices();
        bufferGeometry();
    }
}

void Square::initSquareVertices() {
    if (!posns.empty())
        posns.clear();

    float halfWidth = 0.5f;
    float halfHeight = 0.5f;
    halfWidth = halfHeight * aspectRatio;

    posns.emplace_back(halfWidth, halfHeight, 0.0f);
    posns.emplace_back(halfWidth, -halfHeight, 0.0f);
    posns.emplace_back(-halfWidth, -halfHeight, 0.0f);
    posns.emplace_back(-halfWidth, halfHeight, 0.0f);
}
