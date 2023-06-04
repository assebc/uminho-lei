#define _USE_MATH_DEFINES

#include "../include/Box.h"

using namespace std;

Box::Box(){
  dimensions = 10;
  divisions = 0;
  index = 0;
}

Box::Box(int dim, int n_div){
  dimensions = dim;
  divisions = n_div;
  index = 0;
}

void Box::add_square(bool cam_view, Point3D point_tr, Point3D point_tl, Point3D point_bl, Point3D point_br){
  Triangle t1, t2;
  if(cam_view){
    t1 = Triangle(point_tr.index, point_tl.index, point_bl.index);
    t2 = Triangle(point_tr.index, point_bl.index, point_br.index);
  } else {
    t1 = Triangle(point_tr.index, point_bl.index, point_tl.index);
    t2 = Triangle(point_tr.index, point_br.index, point_bl.index);
  }
  triangles.push_back(t1);
  triangles.push_back(t2);
}

void Box::add_X_face(bool cam_view){
    float yz_incr=1.0*divisions/(1.0*divisions);
    float texture_incr = 1.0/(1.0*divisions);
    int x=cam_view?1:0;
    vector<Point3D> layers;

    for(int y=0;y<=divisions;y++) {
        for(int z=0;z<=divisions;z++) {
            layers.push_back(Point3D(x*divisions,y*yz_incr,z*yz_incr,index++));
            textures.push_back(std::make_pair<float,float>(z*texture_incr,y*texture_incr));
        }
    }
    // Cálculo dos triângulos a desenhar
    for(int y=0;y<divisions;y++) {
        for(int z=0;z<divisions;z++) {
            Point3D topLeft=layers[((divisions+1)*y)+z];
            Point3D topRight=layers[((divisions+1)*y)+z+1];
            Point3D bellowLeft=layers[((divisions+1)*(y+1))+z];
            Point3D bellowRight=layers[((divisions+1)*(y+1))+z+1];
            add_square(cam_view,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
    for(long unsigned int i = 0; i < layers.size(); i++)
        normals.push_back(Point3D(cam_view?1:-1,0,0));
    points.insert(points.end(),layers.begin(),layers.end());
}

void Box::add_Y_face(bool cam_view){
    int y=cam_view?1:0;
    float xz_incr = 1.0f*divisions/(1.0*divisions);
    float texture_incr = 1.0f/(1.0f*divisions);
    vector<Point3D> layers;
    for (int x=0;x<divisions;x++) {
        for (int z=0;z<divisions;z++) {
        layers.push_back(Point3D(x*xz_incr,y*divisions,z*xz_incr,index++));
        textures.push_back(make_pair<float,float>(x*texture_incr,z*texture_incr));
        }
    }

    for(int x=0;x<divisions;x++) {
        for(int z=0;z<divisions;z++) {
            Point3D topLeft=layers[((divisions+1)*x)+z];
            Point3D topRight=layers[((divisions+1)*(x+1))+z];
            Point3D bellowLeft=layers[((divisions+1)*x)+z+1];
            Point3D bellowRight=layers[((divisions+1)*(x+1))+z+1];
            add_square(cam_view,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
    for(long unsigned int i = 0; i < layers.size(); i++)
        normals.push_back(Point3D(0,cam_view?1:-1,0));
    points.insert(points.end(),layers.begin(),layers.end());
}

void Box::add_Z_face(bool cam_view){
    int z=cam_view?1:0;
    float xy_incr = 1.0f*divisions/(1.0*divisions);
    float texture_incr = 1.0f/(1.0f*divisions);
    vector<Point3D> layers;
    for (int y=0;y<divisions;y++) {
        for (int x=0;x<divisions;x++) {
            layers.push_back(Point3D(x*xy_incr,y*xy_incr,z*divisions,index++));
            textures.push_back(make_pair<float,float>(x*texture_incr,y*texture_incr));
        }
    }

    for(int y=0;y<divisions;y++) {
        for(int x=0;x<divisions;x++) {
            Point3D bellowLeft=layers[((divisions+1)*y)+x];
            Point3D bellowRight=layers[((divisions+1)*y)+x+1];
            Point3D topLeft=layers[((divisions+1)*(y+1))+x];
            Point3D topRight=layers[((divisions+1)*(y+1))+x+1];
            add_square(cam_view,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
    for(long unsigned int i = 0; i < layers.size(); i++)
        normals.push_back(Point3D(0,0,cam_view?1:-1));
    points.insert(points.end(),layers.begin(),layers.end());
}

shared_ptr<Model> Box::generate(){
  add_Y_face(false); add_Y_face(true); 
  add_X_face(false); add_X_face(true); 
  add_Z_face(false); add_Z_face(true);
  float radius = sqrt(pow(dimensions,2) * 3);
  return std::make_shared<Model>(points,triangles,radius,normals,textures);
}