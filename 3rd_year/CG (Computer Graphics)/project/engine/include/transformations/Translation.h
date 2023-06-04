#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <vector>

#include "../../../utils/Point3D.h"
#include "Transform.h"

using namespace std;

class Translation : public Transform {
public:
	float x;
	float y;
	float z;
	float time;
	float currentPos = 0;
	int t_before = 0;
	static bool show_curves;
	vector<Point3D> curve_points;
	int type;

	Translation();
	Translation(const Translation& t);
	Translation(float xG, float yG, float zG);
	Translation(float timeG, vector<Point3D> curve_pointsG);
	void applyTransform();

private:
	void multMatrixVector(float* m, Point3D* v, Point3D* res);
	void getCatmullRomPoint(float t, Point3D p0, Point3D p1, Point3D p2, Point3D p3, Point3D& pos, Point3D& deriv);
	void getGlobalCatmullRomPoint(float gt, Point3D& pos, Point3D& deriv);
	void drawCatmullRomCurve();
};