#define _USE_MATH_DEFINES

#include "../include/Cone.h"

using namespace std;

Cone::Cone(){
  radius = 1;
  height = 2;
  stacks = 10;
  slices = 10;
}

Cone::Cone(int rad, int alt, int slic, int stac){
  radius = rad;
  height = alt;
  stacks = slic;
  slices = stac;
}

void Cone::add_top_slice(int slice, int stack, int not_base){
  pair<int,int> prev_slice(slice-not_base,stack);
  pair<int,int> actual_slice(slice*not_base+(1-not_base),stack);

  Point3D top = Point3D(0.0f,height,0.0f,1);
  Point3D prev_point = points[prev_slice];
  Point3D actual_point = points[actual_slice];

  Triangle t = Triangle(top.index,prev_point.index,actual_point.index);
  triangles.push_back(t);
}

void Cone::add_circle_slice(int slice, int stack, int not_base){
  Point3D center = Point3D();

  pair<int,int> prev_slice(slice-not_base,stack);
  pair<int,int> actual_slice(slice*not_base+(1-not_base),stack);

  Point3D prev_point = points[prev_slice];
  Point3D actual_point = points[actual_slice];

  Triangle t = Triangle(center.index,actual_point.index,prev_point.index);
  triangles.push_back(t);
}

void Cone::add_square_slice(int slice, int stack){
    pair<int,int> tr(slice,stack+1);
    pair<int,int> tl(slice-1,stack+1);
    pair<int,int> bl(slice-1,stack);
    pair<int,int> br(slice,stack);

    Point3D point_br = points[br];
    Point3D point_tr = points[tr];
    Point3D point_tl = points[tl];
    Point3D point_bl = points[bl];

    Triangle t1 = Triangle(point_tr.index,point_tl.index,point_bl.index);
    Triangle t2 = Triangle(point_tr.index,point_bl.index,point_br.index);

    triangles.push_back(t1);
    triangles.push_back(t2);
}

void Cone::add_base(int index) {
    double slice_angle_incr=M_PI*2.0/slices;
    vector<Point3D> points;
    for(int slice = 0; slice < slices; slice++) {
        float x=cos(slice_angle_incr*slice)*radius;
        float z=-sinf(slice_angle_incr*slice)*radius;
        textures.push_back(make_pair<float,float>(cos(slice_angle_incr*slice) * 0.1875 + 0.8125,sin(slice_angle_incr*slice) * 0.1875 + 0.1875));
        Point3D ponto =Point3D(x,0,z,index++);
        points.push_back(ponto);
        normals.push_back(Point3D(0.0f,-1.0f,0.0f));
        if(slice==0) continue;
        Triangle t = Triangle(0,index-1,index-2); 
        triangles.push_back(t);
    }
    Triangle t = Triangle(0,points[0].index,index-1);
    triangles.push_back(t);
    vertices.insert(vertices.end(),points.begin(),points.end());
}

void Cone::compute_normals(int stack) {
    for(int i = 0; i <= slices; i++) {
        pair<int,int> before_point((i-1==-1?slices:i-1),stack);
        pair<int,int> after_point((i==slices?0:i+1),stack);
        pair<int,int> actual_point(i,stack);
        Point3D topPoint;
        if(stack != stacks-1) {
            pair<int,int> toppoint(i,stack+1);
            topPoint=points[toppoint];
        }
        else topPoint = Point3D(0.0f,height,0.0f,1);
        Point3D beforePoint=points[before_point];
        Point3D afterPoint=points[after_point];
        Point3D actualPoint=points[actual_point];
        Point3D horizontalVector(afterPoint.x-beforePoint.x,afterPoint.y-beforePoint.y,afterPoint.z-beforePoint.z);
        Point3D verticalVector(topPoint.x-actualPoint.x,topPoint.y-actualPoint.y,topPoint.z-actualPoint.z);
        Point3D normalVector = horizontalVector.cross_product(verticalVector);
        normalVector.normalize();
        normals.push_back(normalVector);
    }
}

shared_ptr<Model> Cone::generate(){

 bool first;
    double slice_angle_incr=M_PI*2.0/slices;
    double height_incr=height/(1.0*stacks);
    int index=1;
    float texture_x_incr= 1.0/(1.0*slices);
    float texture_y_incr = 0.625/(1.0*stacks);
    vertices.push_back(Point3D());
    normals.push_back(Point3D(0,-1,0));
    textures.push_back(make_pair<float,float>(0.8125,0.1875));
    for(int i = 0; i < slices; i++) {
        Point3D top=Point3D(0.0f,height,0.0f,index++);
        vertices.push_back(top);
        normals.push_back(Point3D(0,1,0));
        double textures_x = i * texture_x_incr * 1.0 + (texture_x_incr / 2.0);
        textures.push_back(make_pair<float,float>(float(textures_x),1.0f));
    }
    // Builds everything except base, from top to bottom
    for (int sta=stacks-1;sta>=0;sta--) {
        float y=height_incr*sta;
        float stack_radius=((height-y)*radius)/height;
        first=true;

        for (int slc=0;slc<=slices;slc++) {
            float x = cos(slice_angle_incr*slc)*stack_radius;
            float z = -sinf(slice_angle_incr*slc)*stack_radius;

            Point3D ponto = Point3D(x,y,z,index++);
            vertices.push_back(ponto);
            textures.push_back(make_pair<float,float>(slc*texture_x_incr,sta*texture_y_incr+ 0.375));

            pair<int,int> sliceAndStack(slc,sta);
            points[sliceAndStack]=ponto;

            if (first) {first=false;continue;}
            if (sta==stacks-1) {
                add_top_slice(slc,sta,1);
                if (slc==slices) add_top_slice(slc,sta,0);
            }
            else add_square_slice(slc,sta);
            
        }
        if(sta!=0)
            compute_normals(sta);
        else {
            compute_normals(sta);
            add_base(index);
        }
    }
    return make_shared<Model>(vertices,triangles,height > radius ? height : radius,normals,textures);
}