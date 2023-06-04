#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/transformations/Rotation.h"

Rotation::Rotation(const Rotation& r) {
    degrees = r.degrees;
    time = r.time;
    x = r.x;
    y = r.y;
    z = r.z;
    cc = r.cc;
    type = r.type;
}

Rotation::Rotation(double degreesG, float axisXG, float axisYG, float axisZG) {
    degrees = degreesG;
    x = axisXG;
    y = axisYG;
    z = axisZG;
    cc = 1;
    type = 1;
}

Rotation::Rotation(double timeG, int ccG, float axisXG, float axisYG, float axisZG) {
    time = timeG * 1000.0;
    cc = ccG == 2 ? 1 : -1;
    x = axisXG;
    y = axisYG;
    z = axisZG;
    type = 2;
}

void Rotation::applyTransform() {
    int t = glutGet(GLUT_ELAPSED_TIME);
    if (type == 2) {
        float delta_time = t;
        degrees += (360.0 / time) * delta_time;
    }
    t_before = t;
    glRotatef(degrees * cc, x, y, z);
}