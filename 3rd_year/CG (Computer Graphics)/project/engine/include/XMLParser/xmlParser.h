#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include "../Group.h"
#include "../Figure.h"
#include "tinyxml2.h"
#include "../Camera.h"
#include "../../../utils/Point3D.h"

using namespace tinyxml2;
using namespace std;

class XMLParser{
	public:
		int window_width, window_height;

		XMLParser();
		XMLParser(char * fc);
		XMLParser(string fc);
		Group parseGroup(XMLElement * group);
		shared_ptr<Camera> parseCamera(XMLElement* camera);
		Point3D parsePoint(XMLElement* info);
		vector<Group> parse();
		unordered_set<string> getModels();
		unordered_map<string, Point3D> getCamera();

	private:
		string config_file;
		vector<Group> groups;
		vector<shared_ptr<Point3D>> curve;
		shared_ptr<Camera> camera;
		
};

