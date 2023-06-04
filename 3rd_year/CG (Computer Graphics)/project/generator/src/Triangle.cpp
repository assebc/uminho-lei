#ifdef __TRIANGLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../include/Triangle.h"

using namespace std;

Triangle::Triangle(){
  p1_index = 0;
  p2_index = 0;
  p3_index = 0;
}

Triangle::Triangle(int pa_index, int pb_index, int pc_index){
  p1_index = pa_index;
  p2_index = pb_index;
  p3_index = pc_index;
}