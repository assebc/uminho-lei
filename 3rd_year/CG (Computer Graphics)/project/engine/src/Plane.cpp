#include "../include/Plane.h" 
#include <cmath>

void Plane::setCoefficients(float coef[4]) {
    for (int i = 0; i < 4; i++) {
        coefficients[i] = coef[i];
    }
    float l = sqrt(coefficients[0] * coefficients[0] + coefficients[1] * coefficients[1] + coefficients[2] * coefficients[2]);
    for (int i = 0; i < 4; i++) {
        coefficients[i] /= l;
    }
}

float Plane::distance(Point3D point) {
    float result = point.x * coefficients[0] + point.y * coefficients[1] + point.z * coefficients[2] + coefficients[3];
    return result;
}