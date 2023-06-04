#pragma once

#include <cmath>
#include <string>
#include <memory>

class Point3D {

public:
    float x;
    float y;
    float z;
    int index = 0;

    Point3D();
    Point3D(float x1, float y1, float z1);
    Point3D(float x1, float y1, float z1, int idx);
    Point3D(const Point3D& p);
    void zero();
    void normalize();
    Point3D cross_product(Point3D v2);
    Point3D& operator*(const float& r);
    Point3D& operator+(Point3D& p);
    Point3D& operator*(Point3D& p);
    void operator+=(Point3D& p);
    void operator-=(Point3D& p);
    std::string to_string();
};