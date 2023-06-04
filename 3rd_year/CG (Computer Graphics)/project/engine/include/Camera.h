#pragma once
#include <cstdlib>
#include <GL/glut.h>

#include <tuple>
#include "../../utils/Point3D.h"

using namespace std;

class Camera{

	public :
		Point3D camera_position;
		Point3D camera_lookAt;
		Point3D camera_up;
		Point3D camera_projection;
 
		Camera() = default;

		void addPosition(float x, float y, float z);
		void addLookAt(float x, float y, float z);
		void addUp(float x, float y, float z);
		void addProjection(float fov, float near, float far);

};

