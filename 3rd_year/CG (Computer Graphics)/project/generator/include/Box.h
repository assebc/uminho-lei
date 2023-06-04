#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <memory>
#include <tuple>
#include <map>

#include "../../utils/Point3D.h"
#include "Triangle.h"
#include "Model.h"

class Box{

    public:
        Box();
        Box(int dim,int n_div);
        std::shared_ptr<Model> generate();

    private:
        int dimensions, divisions, index;
        std::vector<Point3D> points;
        std::vector<Triangle> triangles;
        std::vector<Point3D> normals;
        std::vector<std::pair<float,float>> textures;
        void add_square(bool cam_view, Point3D point_br, Point3D point_tr, Point3D point_tl, Point3D point_bl);
        void add_X_face(bool cam_view);
        void add_Y_face(bool cam_view);
        void add_Z_face(bool cam_view);
};