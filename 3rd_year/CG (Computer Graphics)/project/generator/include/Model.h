#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Triangle.h"
#include "../../utils/Point3D.h"

class Model{

    public:
        Model(std::vector<Point3D> point, std::vector<Triangle> trian, float rad, std::vector<Point3D> normal, std::vector<std::pair<float,float>> texture);
        void save_to_file(std::string filename);

    private:
        int n_points, n_triangles;
        float radius;
        std::vector<Triangle> triangles;
        std::vector<Point3D> points;
        std::vector<Point3D> normals;
        std::vector<std::pair<float,float>> textures;
    };