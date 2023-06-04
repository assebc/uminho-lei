#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Transformations/Translation.h"
#define _USE_MATH_DEFINES
#include <math.h>

void buildRotMatrix(Point3D x, Point3D y, Point3D z, float* m) {

	m[0] = x.x; m[1] = x.y; m[2] = x.z; m[3] = 0;
	m[4] = y.x; m[5] = y.y; m[6] = y.z; m[7] = 0;
	m[8] = z.x; m[9] = z.y; m[10] = z.z; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(Point3D a, Point3D b, Point3D& res) {

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
}

float length(Point3D v) {

	float res = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return res;

}

void normalize(Point3D& a) {

	float l = length(a);
	a.x = a.x / l;
	a.y = a.y / l;
	a.z = a.z / l;
}

Translation::Translation() {
	type = 1;
}

Translation::Translation(const Translation& t) {
	x = t.x;
	y = t.y;
	z = t.z;
	time = t.time;
	curve_points = t.curve_points;
	currentPos = t.currentPos;
	t_before = t.t_before;
	type = t.type;
}

Translation::Translation(float xG, float yG, float zG) {
	x = xG;
	y = yG;
	z = zG;
	time = 0;
	show_curves = false;
	type = 1;
}

Translation::Translation(float timeG, vector<Point3D> curve_pointsG) {
	time = timeG * 1000.0;
	curve_points = curve_pointsG;
	type = 2;
}

void Translation::multMatrixVector(float* m, Point3D* v, Point3D* res) {
	for (int j = 0; j < 4; ++j) {
		res[j] = Point3D(0, 0, 0);
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}


void Translation::getCatmullRomPoint(float t, Point3D p0, Point3D p1, Point3D p2, Point3D p3, Point3D& pos, Point3D& deriv) {

	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };

	float tt[4] = { t * t * t,t * t,t,1 };
	float td[4] = { 3 * t * t,2 * t,1,0 };
	Point3D aux[4];
	Point3D pp[4] = { p0,p1,p2,p3 };
	multMatrixVector((float*)m, pp, aux);
	for (int i = 0;i < 4;i++) {
		Point3D pp1 = aux[i] * tt[i];
		Point3D pp2 = aux[i] * td[i];
		pos += pp1;
		deriv += pp2;
	}
}

void Translation::getGlobalCatmullRomPoint(float gt, Point3D& pos, Point3D& deriv) {

	float t = gt * curve_points.size();
	int index = floor(t);
	t = t - index;

	// indices store the points
	int indices[4] = {};
	indices[0] = (index + curve_points.size() - 1) % curve_points.size();
	indices[1] = (indices[0] + 1) % curve_points.size();
	indices[2] = (indices[1] + 1) % curve_points.size();
	indices[3] = (indices[2] + 1) % curve_points.size();


	getCatmullRomPoint(t, curve_points[indices[0]], curve_points[indices[1]], curve_points[indices[2]], curve_points[indices[3]], pos, deriv);
}

void Translation::drawCatmullRomCurve() {
	Point3D res, deriv;

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	for (int i = 0;i < 100;i++) {
		res.zero();
		deriv.zero();
		getGlobalCatmullRomPoint(i / 100.0f, res, deriv);
		glVertex3f(res.x, res.y, res.z);
	}
	glEnd();
}

void Translation::applyTransform() {
	if (type == 2) {
		if (show_curves) drawCatmullRomCurve();
		Point3D res, XX(1, 0, 0), YY(0, 1, 0), ZZ(0, 0, 1);
		getGlobalCatmullRomPoint(currentPos, res, ZZ);

		cross(YY, ZZ, XX);
		cross(ZZ, XX, YY);

		normalize(ZZ);
		normalize(XX);
		normalize(YY);

		glTranslatef(res.x, res.y, res.z);

		float m[16];
		buildRotMatrix(XX, YY, ZZ, m);

		glMultMatrixf(m);

		int t = glutGet(GLUT_ELAPSED_TIME);
		int delta_time = t - t_before;
		t_before = t;

		currentPos += (delta_time / time );
	}
	else glTranslatef(x, y, z);
}