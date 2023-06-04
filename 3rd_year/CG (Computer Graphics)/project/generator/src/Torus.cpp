#define _USE_MATH_DEFINES
#include <math.h>

#include "../include/Torus.h"

using namespace std;

Torus::Torus() {
    innerRadius=2;
    outerRadius=2;
    nSides=10;
    nStacks=10;
}

Torus::Torus(int innerRadiusG,int outerRadiusG,int stacksG,int sidesG) {
    innerRadius=innerRadiusG;
    outerRadius=outerRadiusG;
    nSides=sidesG;
    nStacks=stacksG;
}

void Torus::addSquare(int stacks,int side,int not_last_ring,int not_last_side) {
    pair<int,int> tl(stacks-1,side-1),tr(stacks,side-1);
    pair<int,int> bl(stacks-1,side),br(stacks,side);
    Point3D point_tr=points[tr],point_tl=points[tl];
    Point3D point_bl=points[bl],point_br=points[br];
    Triangle t1=Triangle(point_tr.index,point_tl.index,point_bl.index);
    Triangle t2=Triangle(point_tr.index,point_bl.index,point_br.index);
    triangles.push_back(t1);
    triangles.push_back(t2);
}

void Torus::constructRing(int stacks, float stacks_angle) {
    Point3D nearCenterTop, farCenterTop, nearCenterBot, farCenterBot;
    float xNearCenter = innerRadius * cosf(stacks_angle), xFarCenter = (innerRadius+outerRadius) * cosf(stacks_angle);
    float zNearCenter = innerRadius * sinf(stacks_angle), zFarCenter = (innerRadius+outerRadius) * sinf(stacks_angle);
    nearCenterTop = Point3D(xNearCenter,0,zNearCenter,index++);
    farCenterTop = Point3D(xFarCenter,0,zFarCenter,index++);
    vertices.push_back(nearCenterTop);
    vertices.push_back(farCenterTop);

    nearCenterBot = Point3D(xNearCenter,0,zNearCenter,index++);
    farCenterBot = Point3D(xFarCenter,0,zFarCenter,index++);
    vertices.push_back(nearCenterBot);
    vertices.push_back(farCenterBot);

    normals.push_back(Point3D(0,1,0));
    normals.push_back(Point3D(0,1,0));
    normals.push_back(Point3D(0,-1,0));
    normals.push_back(Point3D(0,-1,0));

    textures.push_back(make_pair<float,float>(0.0f,float(stacks)));
    textures.push_back(make_pair<float,float>(1.0f,float(stacks)));
    textures.push_back(make_pair<float,float>(0.0f,float(stacks)));
    textures.push_back(make_pair<float,float>(1.0f,float(stacks)));

    if(stacks == 0) return;

    Point3D beforeNearCenter, beforeFarCenter;
    beforeNearCenter = vertices[vertices.size()-8];
    beforeFarCenter = vertices[vertices.size()-7];
    Triangle t1=Triangle(farCenterTop.index,beforeNearCenter.index,nearCenterTop.index);
    Triangle t2=Triangle(farCenterTop.index,beforeFarCenter.index,beforeNearCenter.index);
    triangles.push_back(t1);
    triangles.push_back(t2);
    beforeNearCenter = vertices[vertices.size()-6];
    beforeFarCenter = vertices[vertices.size()-5];
    Triangle t3=Triangle(farCenterBot.index,nearCenterBot.index,beforeNearCenter.index);
    Triangle t4=Triangle(farCenterBot.index,beforeNearCenter.index,beforeFarCenter.index);
    triangles.push_back(t3);
    triangles.push_back(t4);
}

// Lean over ring
shared_ptr<Model> Torus::generate() {
    float stack_angle_increment=M_PI*2/nStacks;
    float side_angle_increment=M_PI*2/nSides;
    index=0;

    for (int stack=0;stack<=nStacks;stack++) {

        double stack_angle=stack*stack_angle_increment;
        bool first=true;
        
        float center_x = innerRadius*cosf(stack_angle);
        float center_z = innerRadius*sin(stack_angle);
        if(nSides == 2) {
            constructRing(stack,stack_angle);
            continue;
        }

        for (int side=0;side<=nSides;side++) {        
            double side_angle=side*side_angle_increment;
            float y=outerRadius*sinf(side_angle);
            float distHorizontal=outerRadius*cosf(side_angle);
            float z=(innerRadius+distHorizontal)*sinf(stack_angle);
            float x=(innerRadius+distHorizontal)*cosf(stack_angle);

            Point3D normal = Point3D(x-center_x,y,z-center_z);
            normal.normalize();
            normals.push_back(normal);
            
            textures.push_back(make_pair<float,float>(float(side),float(stack)));

            Point3D ponto=Point3D(x,y,z,index++);
            vertices.push_back(ponto);

            //addPoint
            pair<int,int> StackAndSide(stack,side);
            points[StackAndSide]=ponto;
            if (first) {first=false;continue;} // first iter
            if (stack==0) continue; // insert only points
            else { // make squares
                addSquare(stack,side,1,1);
                if (stack==nStacks-1) { // put together in last ring
                    addSquare(stack,side,0,1);
                }
            }
            if (side==nSides-1) {  // last side
                addSquare(stack,side,1,0);
                if (stack==nStacks-1) {  // put together in last side
                  addSquare(stack,side,0,0);  
                }
            }
        }
    }

    return make_shared<Model>(vertices,triangles,innerRadius+outerRadius,normals,textures);
}