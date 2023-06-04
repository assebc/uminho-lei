#pragma once
#include <cstdlib>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include "transformations/Transform.h"
#include "transformations/Translation.h"
#include "transformations/Rotation.h"
#include "transformations/Scale.h"
#include "Figure.h"

using namespace std;

class Group {
    public:
        vector<shared_ptr<Transform> > transformations;
        unordered_map<string, Figure> models;
        vector<Group> groups;
        bool isDrawn = false;
        float actualMatrix[16];

        Group();
        Group(const Group& g);

        void addTransform(shared_ptr<Transform> t);

        void addFile(string file, float red, float green, float blue);
        void addFile(char* file, float red, float green, float blue);

        void addGroup(Group group);

        unordered_set<string> getModels();

        void updateFigures(vector<float> trans);
};