#define _USE_MATH_DEFINES

#include "../include/Plane.h"

using namespace std;

Plane::Plane(){
    length = 5;
    divisions = 3;
}

Plane::Plane(int len, int n_div){
    length = len;
    divisions = n_div;
}

shared_ptr<Model> Plane::generate(){
    vector<Point3D> points;
    vector<Triangle> triangles;
    vector<Point3D> normals;
    vector<pair<float,float>> textures;
    float x = float(length)/2, z = float(length)/2;
    point_tr = Point3D(-x,0,-z,0);
    point_tl = Point3D(x,0,-z,1);
    point_bl = Point3D(-x,0,z,2);
    point_br = Point3D(x,0,z,3);
    points.push_back(point_tl);
    points.push_back(point_tr);
    points.push_back(point_bl);
    points.push_back(point_br);
    textures.push_back(make_pair<float,float>(1,1));
    textures.push_back(make_pair<float,float>(0,1));
    textures.push_back(make_pair<float,float>(0,0));
    textures.push_back(make_pair<float,float>(1,0));
    t1 = Triangle(point_tr.index,point_tl.index,point_bl.index);
    t2 = Triangle(point_tr.index,point_bl.index,point_br.index);
    triangles.push_back(t1);
    triangles.push_back(t2);
    for(int i = 0; i < 4; i++){
        auto normal = Point3D(0,1,0);
        normals.push_back(normal);
    }

    float radius = sqrt(pow(x,2) + pow(z,2));
    return std::make_shared<Model>(points,triangles,radius,normals,textures);
}
