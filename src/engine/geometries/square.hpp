#pragma once

#include "geometry.hpp"

class Square : public Geometry {
public:
    Square(float aspectRatio = 1.0);
    void init();
    int getIndexNum();
private:
    float aspectRatio;
}
