#include "geometry.hpp"
#include "consoleMsg/consoleMsg.hpp"

#include <memory>

Geometry::Geometry(const uint32_t& indexNum, const float& baseScale, GLenum drawMode) :
    VAO(0), VBO(0), EBO(0), indexNum(indexNum), drawMode(drawMode), baseScale(baseScale) {}

Geometry::~Geometry() {
    glDeleteBuffers(1, &VBO);
    if (indices.size()) {
        glDeleteBuffers(1, &EBO);
    }
    glDeleteVertexArrays(1, &VAO);
}

uint32_t Geometry::getVAO() const {
    return VAO;
}

uint32_t Geometry::getEBO() const {
    return EBO;
}

GLenum Geometry::getDrawMode() const {
    return drawMode;
}

int Geometry::getIndexNum() const {
    return indexNum;
}

bool Geometry::useEBO() const {
    return indices.size() > 0;
}

void Geometry::bufferGeometry() {
    // Initialize vertex data array
    std::vector<float> vertexData;
    vertexData.reserve(posns.size() * 3 + texCoords.size() * 2);

    for (int i = 0; i < posns.size(); ++i) {
        vertexData.push_back(posns[i].x);
        vertexData.push_back(posns[i].y);
        vertexData.push_back(posns[i].z);

        if (texCoords.size()) {
            vertexData.push_back(texCoords[i].x);
            vertexData.push_back(texCoords[i].y);
        }
    }

    // Configure VAO and VBO
    if (!VAO) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    // Configure EBO only if an index array is provided
    if (indices.size()) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(),GL_STATIC_DRAW);
    }

    int stride = 3 * sizeof(float) + (texCoords.size() > 0 ? 2 * sizeof(float) : 0);

    int offset = 0;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    if (texCoords.size() > 0) {
        offset += 3 * sizeof(float);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(1);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
