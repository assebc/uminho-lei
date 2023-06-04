#pragma once
#include <cstdlib>
#include <GL/glut.h>

#include "../../utils/Point3D.h"

class Plane {
private:
public:
    Plane() = default;
    void setCoefficients(float coef[4]);
    float distance(Point3D point);
    float coefficients[4];
};