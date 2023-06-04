#pragma once

#include <vector>
#include <memory>
#include <math.h>

#include "../../utils/Point3D.h"
#include "Triangle.h"
#include "Model.h"

class Plane{

  public:
    Plane();
    Plane(int len,int n_div);
    std::shared_ptr<Model> generate();

  private:
    int length, divisions;
    Triangle t1, t2;
    Point3D point_tl, point_tr, point_bl, point_br;
};