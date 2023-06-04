#include <iostream>

#include "../include/Group.h" 

Group::Group() {
    isDrawn = false;
    float identity[16] = {
        1.0f,  0.0f, 0.0f,  0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    for (int i = 0; i < 16; i++)
        actualMatrix[i] = identity[i];
}

Group::Group(const Group& g1) {
    transformations = g1.transformations;
    models = g1.models;
    groups = g1.groups;
    isDrawn = g1.isDrawn;
    for (int i = 0; i < 16; i++)
        actualMatrix[i] = g1.actualMatrix[i];
}

void Group::addTransform(shared_ptr<Transform> t) {
    transformations.push_back(t);
}

vector<string> split_aux(string str, char separator) {
    vector<string> strings;
    int startIndex = 0, endIndex = 0;
    for (size_t i = 0; i <= str.size(); i++) {

        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

void Group::addFile(string file, float red, float green, float blue) {
    string filename = "../models/" + file;
    ifstream mfile(filename);
    string buffer;
    getline(mfile, buffer);
    vector<string> splitted_line = split_aux(buffer, ' ');
    float rad = stof(splitted_line[2]);
    models[file] = Figure(file, red, green, blue, rad);
}

void Group::addFile(char* file, float red, float green, float blue) {
    string filename = "../models/" + string(file);
    ifstream mfile(filename);
    string buffer;
    getline(mfile, buffer);
    vector<string> splitted_line = split_aux(buffer, ' ');
    float rad = stof(splitted_line[2]);
    models[string(file)] = Figure(string(file), red, green, blue, rad);
}

void Group::addGroup(Group group) {
    groups.push_back(group);
}

unordered_set<string> Group::getModels() {
    unordered_set<string> ret;
    for (auto& m : models) {
        ret.insert(m.first);
    }
    for (auto &gg : groups) {
        unordered_set<string> models = gg.getModels();
        for (auto& file : models) {
            ret.insert(file);
        }
    }
    return ret;
}

void buildTranslationMatrix(float* m, float x, float y, float z) {
    float exempl[16] = {
        1.0f,  0.0f, 0.0f,  x,
        0.0f, 1.0f,  0.0f, y,
        0.0f,  0.0f,  1.0f,  z,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    for (int i = 0; i < 16; i++)
        m[i] = exempl[i];
}

void buildScaleMatrix(float* m, float x, float y, float z) {
    float exempl[16] = {
        x,  0.0f, 0.0f,  0.0f,
        0.0f, y,  0.0f, 0.0f,
        0.0f,  0.0f,  z,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    for (int i = 0; i < 16; i++)
        m[i] = exempl[i];
}

void buildRotationMatrix(float* m, float x, float y, float z, float deg) {
    float rad = deg * (M_PI / 180.0f);
    if (x) {
        float exempl[16] = {
        1.0f,  0.0f, 0.0f,  0.0f,
        0.0f, cos(rad),  -sin(rad), 0.0f,
        0.0f,  sin(rad),  cos(rad),  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
        };
        for (int i = 0; i < 16; i++)
            m[i] = exempl[i];
    }
    else if (y) {
        float exempl[16] = {
        cos(rad),  0.0f, sin(rad),  0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        -sin(rad),  0.0f,  cos(rad),  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
        };
        for (int i = 0; i < 16; i++)
            m[i] = exempl[i];
    }
    else if (z) {
        float exempl[16] = {
        cos(rad),  -sin(rad), 0.0f,  0.0f,
        sin(rad), cos(rad),  0.0f, 0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
        };
        for (int i = 0; i < 16; i++)
            m[i] = exempl[i];
    }
}

void multMat(float* a, float* b, float* res) {
    float r[16] = {};
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            r[i * 4 + j] = 0.0;
            for (int k = 0; k < 4; k++) {
                r[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
            }
        }
    }
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            res[i * 4 + j] = r[i * 4 + j];
        }
    }
}

void calcPoint(float* m, float* p, float* res) {
    res[0] = res[1] = res[2] = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i] += m[i * 4 + j] * p[j];
        }
    }
}

// trans[0] == 0 -> Translation else trans[0] == 1 -> Scale else -> Rotation
void Group::updateFigures(vector<float> trans) {
    float m[16];
    float centre[4] = { 0,0,0,1 };
    if (trans.size() != 0) {
        for (auto& figure : models) {
            if (trans[0] == 0) {
                buildTranslationMatrix(m, trans[1], trans[2], trans[3]);
                multMat(actualMatrix, m, actualMatrix);
                float temp[4];
                calcPoint(actualMatrix, centre, temp);
                figure.second.centerPoint.x = temp[0];
                figure.second.centerPoint.y = temp[1];
                figure.second.centerPoint.z = temp[2];
            }
            else if (trans[0] == 1 && !isDrawn) {
                buildScaleMatrix(m, trans[1], trans[2], trans[3]);
                multMat(actualMatrix, m, actualMatrix);
                float max;
                if (trans[1] > trans[2])
                    max = trans[1];
                else
                    max = trans[2];
                if (max < trans[3])
                    max = trans[3];
                figure.second.radius *= max;
            }
            else if (trans[0] == 2) {
                buildRotationMatrix(m, trans[1], trans[2], trans[3], trans[4]);
                multMat(actualMatrix, m, actualMatrix);
                float temp[4];
                calcPoint(actualMatrix, centre, temp);
                figure.second.centerPoint.x = temp[0];
                figure.second.centerPoint.y = temp[1];
                figure.second.centerPoint.z = temp[2];
            }
        }
        for (auto& group : groups) {
            group.updateFigures(trans);
        }
    }
}