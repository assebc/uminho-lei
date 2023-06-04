#include "../include/Figure.h"

Figure::Figure() {
    filename = "";
    radius = 0;
    red = 0;
    green = 0;
    blue = 0;
    centerPoint = Point3D(0, 0, 0);
}

Figure::Figure(const Figure& fig) {
    filename = fig.filename;
    red = fig.red;
    green = fig.green;
    blue = fig.blue;
    radius = fig.radius;
    centerPoint = fig.centerPoint;
}

Figure::Figure(std::string file, float red_color, float green_color, float blue_color, float rad) {
	filename = file;
	red = red_color;
	green = green_color;
	blue = blue_color;
	radius = rad;
	centerPoint = Point3D(0, 0, 0);
}