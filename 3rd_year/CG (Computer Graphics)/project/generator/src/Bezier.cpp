#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "../include/Bezier.h"
#include "../../Utils/Point3D.h"

using namespace std;
using std::ifstream;

Bezier::Bezier(string patch_files,int tesselation_levels) {
	patch_file=patch_files;
	vertical_tesselation=tesselation_levels;
	horizontal_tesselation=tesselation_levels;
	vertical_tesselation_inc=1.0/vertical_tesselation;
	horizontal_tesselation_inc=1.0/horizontal_tesselation;
	maxDistance = 0;
	Point3D p1 = Point3D(1,1,1);
	Point3D p_1 = Point3D(p1*-1);
	Point3D p3 = Point3D(p1*3);
	Point3D p_3 = Point3D(p1*-3);
	Point3D p_6 = Point3D(p1*-6);
	Point3D p0 = Point3D(p1*0);
	vector<Point3D> row0,row1,row2,row3;
	row0.push_back(p_1);row0.push_back(p3);row0.push_back(p_3);row0.push_back(p1);
	row1.push_back(p3);row1.push_back(p_6);row1.push_back(p3);row1.push_back(p0);
	row2.push_back(p_3);row2.push_back(p3);row2.push_back(p0);row2.push_back(p0);
	row3.push_back(p1);row3.push_back(p0);row3.push_back(p0);row3.push_back(p0);
	bezier_matrix.push_back(row0);
	bezier_matrix.push_back(row1);
	bezier_matrix.push_back(row2);
	bezier_matrix.push_back(row3);
}

vector<vector<Point3D>> Bezier::multiplyMatrix(vector<vector<Point3D>> m1,vector<vector<Point3D>> m2) {
	vector<vector<Point3D>> returnMatrix;
	for(long unsigned int i=0;i<m1.size();i++) {    
		vector<Point3D> row;
		for(long unsigned int j=0;j<m2[0].size();j++) {  
			Point3D point=Point3D(0,0,0);
			for(long unsigned int k=0;k<m1[0].size();k++) { 
				point+=m1[i][k]*m2[k][j];    
			}
			row.push_back(point);    
		}
		returnMatrix.push_back(row);    
	}
	return returnMatrix;
}


void Bezier::parsePatches() {
    int num_points;
	string p;
	string x,y,z;
	string comma;
	map<int,vector<int>> index_patches;
	vector<Point3D> patch_points;
    
    ifstream fp("patches/" + patch_file);

	fp >> num_patches;
	for (int i=0;i<num_patches;i++) {
		for (int j=0;j<16;j++) {
			fp >> p;
			if (j!=15) p.pop_back();
			index_patches[i].push_back(stoi(p));
		}
    }

	fp >> num_points;

	for (int i=0;i<num_points;i++) {
		// mantain axis
		fp >> z >> x >> y;
		z.pop_back();
		x.pop_back();
 		Point3D point = Point3D(strtof(x.c_str(),NULL),strtof(y.c_str(),NULL),strtof(z.c_str(),NULL));
		patch_points.push_back(point);
    }

	// FIXME: to be enhanced
	for (int i=0;i<num_patches;i++) {
		Patch patch = Patch();
		for (int j=0;j<4;j++) {
			vector<Point3D> row;
			patch.points.push_back(row);
			for (int k=0;k<4;k++) {
				int index=index_patches[i][j*4+k];
				patch.points[j].push_back(patch_points[index]);
			}
		}
		patches.push_back(patch);
	}
}

float Bezier::distance(float x,float y,float z) {
	return sqrt(x*x + y*y + z*z);
}

void Bezier::computeNormal(std::vector<std::vector<Point3D>> preCalculatedMatrix, float u, float v, std::vector<std::vector<Point3D>> u_matrix, std::vector<std::vector<Point3D>> v_matrix) {
	std::vector<std::vector<Point3D>> u_der_matrix,v_der_matrix;
	std::vector<Point3D> rowu;
	Point3D uPoint = Point3D(3 * u * u, 3*u*u,3*u*u);
	rowu.push_back(uPoint);
	uPoint = Point3D(2 * u, 2 * u, 2 * u);
	rowu.push_back(uPoint);
	uPoint = Point3D( 1, 1, 1);
	rowu.push_back(uPoint);
	uPoint = Point3D(0, 0, 0);
	rowu.push_back(uPoint);
	u_der_matrix.push_back(rowu);

	// Create v derivative matrix
	std::vector<Point3D> rowv1,rowv2,rowv3,rowv4;
	Point3D vPoint = Point3D(3 * v * v, 3*v*v,3*v*v);
	rowv1.push_back(vPoint);
	v_der_matrix.push_back(rowv1);
	vPoint = Point3D(2 * v, 2 * v, 2 * v);
	rowv2.push_back(vPoint);
	v_der_matrix.push_back(rowv2);
	vPoint = Point3D( 1, 1, 1);
	rowv3.push_back(vPoint);
	v_der_matrix.push_back(rowv3);
	vPoint = Point3D(0, 0, 0);
	rowv4.push_back(vPoint);
	v_der_matrix.push_back(rowv4);

	// Calculo derivada parcial horizontal
	auto auxMatrix = multiplyMatrix(u_der_matrix,preCalculatedMatrix);
	auto finalMatrix = multiplyMatrix(auxMatrix,v_matrix);
	Point3D uPointDer = finalMatrix[0][0];

	// Calculo derivada parcial vertical
	auto auxMatrix2 = multiplyMatrix(u_matrix,preCalculatedMatrix);
	auto finalMatrix2 = multiplyMatrix(auxMatrix2,v_der_matrix);
	Point3D vPointDer = finalMatrix2[0][0];

	// Produto externo para obter normal
	Point3D normal = vPointDer.cross_product(uPointDer);
	normal.normalize();
	normals.push_back(normal);
}

Point3D Bezier::calculatePoint(vector<vector<Point3D>> preCalculatedMatrix,int vertical_level,int horizontal_level) {
	float u = vertical_level*vertical_tesselation_inc;
	float v = horizontal_level*horizontal_tesselation_inc;
	vector<vector<Point3D>> u_matrix,v_matrix;
	vector<Point3D> rowu;
	for (int i=3;i>=0;i--) {
		vector<Point3D> rowv;
		float uValue = pow(u,i);
		float vValue = pow(v,i);
		Point3D uPoint = Point3D(uValue,uValue,uValue);
		Point3D vPoint = Point3D(vValue,vValue,vValue);
		rowu.push_back(uPoint);
		rowv.push_back(vPoint);
		v_matrix.push_back(rowv);
	}
	u_matrix.push_back(rowu);
	auto auxMatrix = multiplyMatrix(u_matrix,preCalculatedMatrix);
	auto returnMatrix = multiplyMatrix(auxMatrix,v_matrix);
	computeNormal(preCalculatedMatrix,u,v,u_matrix,v_matrix);
	textures.push_back(make_pair<float,float>((double)u,(double)v));
	float dis = distance(returnMatrix[0][0].x,returnMatrix[0][0].y,returnMatrix[0][0].z);
	maxDistance = dis > maxDistance ? dis : maxDistance;
	return returnMatrix[0][0];
}

void Bezier::calculatePoints(vector<vector<Point3D>> preCalculatedMatrix,int& indexPoint,vector<Point3D>& vertixes,vector<Triangle>& triangs) {
	for (int i=0;i<=vertical_tesselation;i++){
		for (int j=0;j<=horizontal_tesselation;j++) {
			auto point = calculatePoint(preCalculatedMatrix,i,j);
			point.index=indexPoint;

			float y=point.y;float x=point.x;
			point.y=point.z;point.x=y;
			point.z=x;
			vertixes.push_back(point);
			if (i && j) {
			    triangs.push_back(Triangle(indexPoint-horizontal_tesselation-2,indexPoint-horizontal_tesselation-1,indexPoint));
			    triangs.push_back(Triangle(indexPoint-1,indexPoint-horizontal_tesselation-2,indexPoint));
            }
            indexPoint++;
        }
	}
}

shared_ptr<Model> Bezier::generate() {

	parsePatches();

	int indexPoint=0;
	vector<Point3D> vertices;
	vector<Triangle> triangles;
	for (int i=0;i<num_patches;i++) {
		Patch p = patches[i];

		auto auxMatrix = multiplyMatrix(bezier_matrix,p.points);
		auto preCalculatedMatrix = multiplyMatrix(auxMatrix,bezier_matrix);
		calculatePoints(preCalculatedMatrix,indexPoint,vertices,triangles);
	}
	return make_shared<Model>(vertices,triangles,maxDistance,normals,textures);
}