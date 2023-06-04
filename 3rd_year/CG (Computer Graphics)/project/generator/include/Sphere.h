#pragma once

#include <vector>
#include <memory>
#include <math.h>
#include <map>

#include "../../utils/Point3D.h"
#include "Triangle.h"
#include "Model.h"


class Sphere{
  
    public:
        Sphere();
        Sphere(int radius, int slice, int stack);
        std::shared_ptr<Model> generate();

    private:
        int radius, slices, stacks;
        void add_top_bottom_slice(bool top, int slice, int stack, int last);
        void add_square_slice(int slice, int stack, int last);
        std::map<std::pair<int,int>,Point3D> points;
        std::vector<Triangle> triangles;
        std::vector<Point3D> normals;
        std::vector<std::pair<float,float>> textures;
};