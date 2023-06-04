#include "Point3D.h"

Point3D::Point3D() {
	x = 0;
	y = 0;
	z = 0;
	index = 0;
}

Point3D::Point3D(float x1, float y1, float z1) {
	x = x1;
	y = y1;
	z = z1;
}

Point3D::Point3D(float x1, float y1, float z1, int idx) {
	x = x1;
	y = y1;
	z = z1;
	index = idx;
}

Point3D::Point3D(const Point3D& p) {
	x = p.x;
	y = p.y;
	z = p.z;
	index = p.index;
}

void Point3D::zero() {
	x = 0;
	y = 0;
	z = 0;
}

void Point3D::normalize() {
	float l = sqrt(x * x + y * y + z * z);
	if (l != 0) {
		x = x / l;
		y = y / l;
		z = z / l;
	}
}

Point3D Point3D::cross_product(Point3D v2) {
	float rx = y * v2.z - z * v2.y;
	float ry = z * v2.x - x * v2.z;
	float rz = x * v2.y - y * v2.x;
	return Point3D(rx, ry, rz);
}

void Point3D::operator-=(Point3D& p) {
	x -= p.x;
	y -= p.y;
	z -= p.z;
}
void Point3D::operator+=(Point3D& p) {
	x += p.x;
	y += p.y;
	z += p.z;
}

Point3D& Point3D::operator+(Point3D& p) {
	std::shared_ptr<Point3D> res = std::make_shared<Point3D>(this->x + p.x, this->y + p.y, this->z + p.z);
	return *res;
}

Point3D& Point3D::operator*(Point3D& r) {
	std::shared_ptr<Point3D> res = std::make_shared<Point3D>(x * r.x, y * r.y, z * r.z);
	return *res;
}

Point3D& Point3D::operator*(const float& r) {
	std::shared_ptr<Point3D> res = std::make_shared<Point3D>(x * r, y * r, z * r);
	return *res;
}

std::string Point3D::to_string() {
	return
		"\nX: " + std::to_string(x) +
		"\nY: " + std::to_string(y) +
		"\nZ: " + std::to_string(z);
}