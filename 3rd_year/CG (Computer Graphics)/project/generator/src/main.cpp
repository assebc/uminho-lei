#ifdef __MAIN__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <string>
#include <iostream>

#include "../include/Model.h"
#include "../include/Box.h"
#include "../include/Cone.h"
#include "../include/Plane.h"
#include "../include/Sphere.h"
#include "../include/Torus.h"
#include "../include/Bezier.h"

using namespace std;

int main(const int argc, char * argv[]){

  string filename;
  shared_ptr<Model> m;

  if (argc>2){
    string primitives = string(argv[1]);

    if (primitives=="plane"){
      if(argc != 5){
        cout << "Number of arguments is different then 5 (five)!" << endl;
        return 1;
      }
      int length = atoi(argv[2]), divisions = atoi(argv[3]);
      Plane p = Plane(length,divisions);
      m = p.generate();
      filename = string(argv[4]);

    } else if (primitives=="box"){

      if(argc != 5){
        cout << "Number of arguments is different then 5 (five)!" << endl;
        return 1;
      }
      int dimensions = atoi(argv[2]), divisions = atoi(argv[3]);
      Box b = Box(dimensions,divisions);
      m = b.generate();
      filename = string(argv[4]);

    } else if (primitives=="sphere"){

      if(argc != 6){
        cout << "Number of arguments is different then 6 (six)!" << endl;
        return 1;
      }
      int radius = atoi(argv[2]), slices = atoi(argv[3]), stacks = atoi(argv[4]);
      Sphere s = Sphere(radius,slices,stacks);
      m = s.generate();
      filename = string(argv[5]);

    } else if (primitives=="cone"){

      if (argc != 7){
        cout << "Number of arguments is different then 7 (seven)!" << endl;
        return 1;
      }
      int radius = atoi(argv[2]), height = atoi(argv[3]), slices = atoi(argv[4]), stacks = atoi(argv[5]);
      Cone c = Cone(radius,height,slices,stacks);
      m = c.generate();
      filename = string(argv[6]);
    } else if (primitives=="torus"){

      if(argc != 7){
        cout << "Number of arguments is different then 7 (seven)!" << endl;
        return 1;
      }
      int innerRadius = atoi(argv[2]), outerRadius = atoi(argv[3]), rings = atoi(argv[4]), sides = atoi(argv[5]);
      Torus t = Torus(innerRadius, outerRadius, rings, sides);
      m = t.generate();
      filename = string(argv[6]);
    } else if (primitives=="patch"){
      if(argc != 5){
        cout << "Number of arguments is different then 5 (five)!" << endl;
        return 1;
      }
      string patch_file = string(argv[2]);
      int tesselation_level = atoi(argv[3]);
      Bezier b = Bezier(patch_file, tesselation_level);
      m = b.generate();
      filename = string(argv[4]);
    } else{
      cout << "Graphical Primitive type is incorret, please try again!" << endl;
      return 1;
    }

    m->save_to_file(filename);

  } else {
    cout << "Input needs to have all the parameters for each graphical primitive" << endl;
  }
  return 0;

}



