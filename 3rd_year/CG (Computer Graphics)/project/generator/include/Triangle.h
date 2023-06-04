#pragma once

#include <iostream>

#include "../../utils/Point3D.h"

class Triangle{

  public:
    int p1_index, p2_index, p3_index;
    Triangle();
    Triangle(int pa_index, int pb_index, int pc_index);
};