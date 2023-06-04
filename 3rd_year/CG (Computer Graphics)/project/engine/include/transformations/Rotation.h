#pragma once 

#include <vector>
#include "Transform.h"

class Rotation : public Transform {

public:
	double degrees;
	float x;
	float y;
	float z;
	float time;
	int t_before;
	int cc;
	int type;

	Rotation(const Rotation& r);
	Rotation(double degreesG, float axisXG, float axisYG, float axisZG);
	Rotation(double timeG, int ccG, float axisXG, float axisYG, float axisZG);
	void applyTransform();

};