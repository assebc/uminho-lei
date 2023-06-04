#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <memory>
#include <iostream>

#include "../../utils/Point3D.h"
#include "Triangle.h"
#include "Model.h"

class Patch{

    public:
        Patch()=default;
        std::vector<std::vector<Point3D>> points;
};