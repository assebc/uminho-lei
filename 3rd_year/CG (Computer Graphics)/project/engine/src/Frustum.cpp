#include <iostream>

#include "../include/Frustum.h" 

#define m(row,col) m[col*4+row-5]

void Frustum::calculatePlanes() {
	float m[16], p[16], res[16];
	glGetFloatv(GL_PROJECTION_MATRIX, p);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glPushMatrix();
	glLoadMatrixf(p);
	glMultMatrixf(m);
	glGetFloatv(GL_MODELVIEW_MATRIX, res);
	glPopMatrix();
	applyPlanes(res);

}

void Frustum::applyPlanes(float* m) {
	float coefs[4] = { m(3,1) + m(4,1),
				 m(3,2) + m(4,2),
				 m(3,3) + m(4,3),
				 m(3,4) + m(4,4) };
	planes[NEAR].setCoefficients(coefs);
	coefs[0] = -m(3, 1) + m(4, 1); coefs[1] = -m(3, 2) + m(4, 2); coefs[2] = -m(3, 3) + m(4, 3); coefs[3] = -m(3, 4) + m(4, 4);
	planes[FAR].setCoefficients(coefs);
	coefs[0] = m(2, 1) + m(4, 1); coefs[1] = m(2, 2) + m(4, 2); coefs[2] = m(2, 3) + m(4, 3); coefs[3] = m(2, 4) + m(4, 4);
	planes[BOT].setCoefficients(coefs);
	coefs[0] = -m(2, 1) + m(4, 1); coefs[1] = -m(2, 2) + m(4, 2); coefs[2] = -m(2, 3) + m(4, 3); coefs[3] = -m(2, 4) + m(4, 4);
	planes[TOP].setCoefficients(coefs);
	coefs[0] = m(1, 1) + m(4, 1); coefs[1] = m(1, 2) + m(4, 2); coefs[2] = m(1, 3) + m(4, 3); coefs[3] = m(1, 4) + m(4, 4);
	planes[LEFT].setCoefficients(coefs);
	coefs[0] = -m(1, 1) + m(4, 1); coefs[1] = -m(1, 2) + m(4, 2); coefs[2] = -m(1, 3) + m(4, 3); coefs[3] = -m(1, 4) + m(4, 4);
	planes[RIGHT].setCoefficients(coefs);
}

int Frustum::sphereInFrustum(Point3D p, float radius) {
	float distance;
	int result = INSIDE;
	for (int i = 0; i < 6; i++) {
		distance = planes[i].distance(p);
		if (distance < 0)
			if (radius < std::abs(distance))
				return OUTSIDE;
	}
	return(result);
}