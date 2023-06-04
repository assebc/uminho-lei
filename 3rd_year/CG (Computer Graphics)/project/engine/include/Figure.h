#pragma once

#include <string>
#include "../../utils/Point3D.h"

class Figure {
	
	public:
		std::string filename;
		float red, green, blue, radius;
		Point3D centerPoint;

		Figure();
		Figure(const Figure& fig);
		Figure(std::string file, float red_color, float green_color, float blue_color, float rad);
};