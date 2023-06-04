#define _USE_MATH_DEFINES

#include "../include/Sphere.h"

using namespace std;

Sphere::Sphere(){
    radius = 1;
    slices = 10;
    stacks = 10;
}

Sphere::Sphere(int rad, int slic, int sta){
    radius = rad;
    slices = slic;
    stacks = sta;
}

void Sphere::add_top_bottom_slice(bool top, int slice, int stack, int last){
    Triangle t;
    Point3D up = Point3D(0.0f,float(radius),0.0f,0);
    Point3D down = Point3D(0.0f,-float(radius),0.0f,1);
    pair<int,int> prev_slice(slice-last,stack);
    pair<int,int> actual_slice(slice*last+(1-last),stack);
    Point3D snd = points[prev_slice];
    Point3D thrd = points[actual_slice];
    if(top) t = Triangle(up.index, snd.index, thrd.index);
    else t = Triangle(down.index, thrd.index, snd.index);
    triangles.push_back(t);
    }

    void Sphere::add_square_slice(int slice, int stack, int last){
    pair<int,int> tl(slice-last,stack-1);
    pair<int,int> bl(slice-last,stack);
    pair<int,int> tr(slice*last+(1-last),stack-1);
    pair<int,int> br(slice*last+(1-last),stack);
    Point3D point_tr = points[tr];
    Point3D point_tl = points[tl];
    Point3D point_bl = points[bl];
    Point3D point_br = points[br];
    Triangle t1 = Triangle(point_tr.index,point_tl.index,point_bl.index);
    Triangle t2 = Triangle(point_tr.index,point_bl.index,point_br.index);
    triangles.push_back(t1);
    triangles.push_back(t2);
    }

shared_ptr<Model> Sphere::generate(){
    double slice_angle_incr=M_PI*2.0/slices;
    double stack_angle_incr=M_PI/stacks;
    float texture_x_incr = 1.0f/(1.0f*slices);
    float texture_y_incr = 1.0f/(1.0f*stacks);

    int index=2;
    vector<Point3D> vertices;
    Point3D up= Point3D(0.0f,radius,0.0f,0);
    Point3D down = Point3D(0.0f,-radius,0.0f,1);
    vertices.push_back(up);
    vertices.push_back(down);

    for(int i = 0;i<slices;i++){
        Point3D top = Point3D(0.0f,radius,0.0f,index++);
        Point3D bottom = Point3D(0.0f,-radius,0.0f,index++);
        vertices.push_back(top);
        vertices.push_back(bottom);
        normals.push_back(Point3D(0.0f,1.0f,0.0f));
        normals.push_back(Point3D(0.0f,-1.0f,0.0f));
        double textures_x = i * texture_x_incr * 1.0 + (texture_x_incr / 2.0);
        textures.push_back(make_pair<float,float>(float(textures_x),1.0f));
        textures.push_back(make_pair<float,float>(float(textures_x),0.0f));
    }

    for (int stack=1;stack<stacks;stack++) {
        double stack_angle=stack*stack_angle_incr;
        float y=radius*cosf(stack_angle);
        float stack_radius=radius*sinf(stack_angle);
        bool first=true;

        for (int slice=0;slice<=slices;slice++) {
            double slice_angle=slice*slice_angle_incr;
            float x=stack_radius*cosf(slice_angle);
            float z=-stack_radius*sinf(slice_angle);

            Point3D p = Point3D(x,y,z,index++);
            vertices.push_back(p);

            Point3D normal = Point3D(x,y,z);
            normal.normalize();
            normals.push_back(normal);
            textures.push_back(make_pair<float,float>(slice*texture_x_incr,(stacks-stack)*texture_y_incr));

            pair<int,int> pos(slice,stack);
            points[pos] = p;
            if (first) {first=false;continue;}
            if (stack==1) {
                add_top_bottom_slice(true,slice,stack,1);
                if (slice==slices) add_top_bottom_slice(true,slice,stack,0);
            }
            else {
                add_square_slice(slice,stack,1);
                if (slice==slices) add_square_slice(slice,stack,0);
            }
            if (stack==stacks-1) {
                add_top_bottom_slice(false,slice,stack,1);
                if (slice==slices) add_top_bottom_slice(false,slice,stack,0);
            }
        }
    }

    return make_shared<Model>(vertices,triangles,radius,normals,textures);
}
