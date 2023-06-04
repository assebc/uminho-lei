#include "../include/Model.h"

using std::ofstream;
using std::to_string;
using namespace std;

Model::Model(vector<Point3D> vertixes, vector<Triangle> trian, float rad, vector<Point3D> normal, vector<pair<float,float>> texture){
  points = vertixes;
  triangles = trian;
  n_points = points.size();
  n_triangles = triangles.size();
  radius = rad;
  normals = normal;
  textures = texture;
}

void Model::save_to_file(string filename){
  string file = "/engine/models/" + filename;
  ofstream cfile(filename);
  if(cfile){
    cfile << to_string(n_points) << " " << to_string(n_triangles) << " " << to_string(radius) << endl;
    for (int i=0;i<n_points;i++) {
      cfile << to_string(points[i].x) << " " << to_string(points[i].y) << " " << to_string(points[i].z) << endl; 
    }
    for (int j=0;j<n_triangles;j++) {
      cfile << to_string(triangles[j].p1_index) << " " << to_string(triangles[j].p2_index) << " " << to_string(triangles[j].p3_index) << endl; 
    }
    for (int i=0;i<n_points;i++) {
      cfile << to_string(normals[i].x) << " " << to_string(normals[i].y) << " " << to_string(normals[i].z) << endl; 
    }
    for (int i=0;i<n_points;i++) {
      cfile << to_string(textures[i].first) << " " << to_string(textures[i].second) << endl; 
    }
    cfile.close();

  } else{
    cerr << "error while opening file " + file << endl;
    exit(1);
  }

}
