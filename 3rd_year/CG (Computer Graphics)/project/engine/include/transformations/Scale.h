#pragma once

#include "Transform.h"

class Scale : public Transform {

public:
	float x;
	float y;
	float z;

	Scale(float xt, float yt, float zt);
	void applyTransform();

};