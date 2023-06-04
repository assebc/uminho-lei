#pragma once

#include <vector>
#include <string>
#include <memory>
#include <math.h>
#include <map>

#include "../../utils/Point3D.h"
#include "Triangle.h"
#include "Model.h"

class Cone{
  
	public:
		Cone();
		Cone(int rad, int alt, int slic, int stac);
		std::shared_ptr<Model> generate();

	private:
		int radius, height, stacks, slices;
		std::map<std::pair<int,int>,Point3D> points;
		std::vector<Point3D> vertices;
		std::vector<Triangle> triangles;
		std::vector<Point3D> normals;
        std::vector<std::pair<float,float>> textures;
		void compute_normals(int stack);
		void add_base(int index);
		void add_top_slice(int slice,int stack,int not_last);
		void add_circle_slice(int slice,int stack,int not_last);
		void add_square_slice(int slice,int stack);
};