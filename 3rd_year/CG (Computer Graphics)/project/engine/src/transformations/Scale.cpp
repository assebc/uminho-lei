#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/transformations/Scale.h"

Scale::Scale(float xt, float yt, float zt) {
    x = xt;
    y = yt;
    z = zt;
}

void Scale::applyTransform() {
    glScalef(x, y, z);
}