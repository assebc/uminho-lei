#pragma once

#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../../utils/Point3D.h"
#include "Triangle.h"
#include "Patch.h"
#include "Model.h"

class Bezier{

    public:
        Bezier();
        Bezier(std::string patch_file, int tesselation_level);
        void parsePatches();
        std::shared_ptr<Model> generate();
        float maxDistance;
    private:
        int vertical_tesselation, horizontal_tesselation, num_patches;
        float vertical_tesselation_inc, horizontal_tesselation_inc;
        std::vector<std::vector<Point3D>> bezier_matrix;
        std::string patch_file;
        std::vector<Patch> patches;
        std::vector<Point3D> normals;
        std::vector<std::pair<float,float>> textures;
        void computeNormal(std::vector<std::vector<Point3D>> preCalculatedMatrix, float u, float v, std::vector<std::vector<Point3D>> u_matrix, std::vector<std::vector<Point3D>> v_matrix);
        std::vector<std::vector<Point3D>> multiplyMatrix(std::vector<std::vector<Point3D>> m1, std::vector<std::vector<Point3D>> m2);
        Point3D calculatePoint(std::vector<std::vector<Point3D>> pre_calc_matrix, int vertical_level, int horizontal_level);
        void calculatePoints(std::vector<std::vector<Point3D>> pre_calc_matrix, int& indexPoint, std::vector<Point3D>& vertices, std::vector<Triangle>& triangles);
        float distance(float x,float y,float z);
};
