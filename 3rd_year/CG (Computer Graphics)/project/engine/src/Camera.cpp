#include "../include/Camera.h"

using namespace std;

void Camera::addPosition(float x, float y, float z) {
	camera_position = Point3D(x,y,z);
}

void Camera::addLookAt(float x, float y, float z) {
	camera_lookAt = Point3D(x, y, z);
}

void Camera::addUp(float x, float y, float z) {
	camera_up = Point3D(x, y, z);
}

void Camera::addProjection(float fov, float near, float far) {
	camera_projection = Point3D(fov, near, far);
}
