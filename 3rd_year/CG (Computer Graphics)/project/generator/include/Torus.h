#pragma once

#include <vector>
#include <map>
#include <memory>
#include <string>

#include "../../utils/Point3D.h"
#include "Triangle.h"
#include "Model.h"

class Torus {
    public:
        Torus();
        Torus(int innerRadiusG,int outerRadiusG,int stacksG,int sidesG);
        void addSquare(int stacks,int sides,int not_last_ring,int not_last_side);
        void constructRing(int stacks, float ring_angle);
        std::shared_ptr<Model> generate();
        
    private:
        int innerRadius,outerRadius,nStacks,nSides,index;
        std::vector<Point3D> vertices;
        std::vector<Triangle> triangles;
        std::map<std::pair<int,int>,Point3D> points;
        std::vector<Point3D> normals;
        std::vector<std::pair<float,float>> textures;
};

