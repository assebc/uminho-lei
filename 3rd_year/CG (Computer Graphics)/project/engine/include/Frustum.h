#pragma once
#include <cstdlib>
#include <GL/glut.h>

#include "../../utils/Point3D.h"
#include "../include/Plane.h"

class Frustum {
private:
    void applyPlanes(float* matrix);
    enum {
        TOP = 0, BOT, LEFT, RIGHT, NEAR, FAR
    };
public:
    enum {
        INSIDE = 0, OUTSIDE
    };
    Plane planes[6];
    int sphereInFrustum();
    Frustum() = default;
    void calculatePlanes();
    int sphereInFrustum(Point3D p, float radius);
};