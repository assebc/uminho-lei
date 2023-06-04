#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <fstream>
#include <memory>

#include "../include/XMLParser/xmlParser.h"
#include "../include/Group.h"
#include "../include/VBO.h"
#include "../include/Figure.h"
#include "../include/Frustum.h"

using std::ifstream;
using namespace std;

constexpr int BUFFER_SIZE = 1024;

bool Translation::show_curves = false;
int window_width = 800, window_height = 800;
unordered_map<string, Point3D> camera;
unordered_map<string, VBO> buffers;
vector<Group> groups;
Frustum frustum;
bool see_axis = true, draw_mode = true, enableFrustum = false;
float alpha = 10.0f, beta = 250;
GLfloat x_scale = 1.0f, y_scale = 1.0f, z_scale = 1.0f;
int startX, startY, tracking = 0;
int boost = 1;

void drawAxis() {
    glBegin(GL_LINES);
    // X Axis is Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10000.0f, 0.0f, 0.0f);
    glVertex3f(10000.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10000.0f, 0.0f);
    glVertex3f(0.0f, 10000.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10000.0f);
    glVertex3f(0.0f, 0.0f, 10000.0f);
    glEnd();
}

void drawFigure(Figure figure) {
    VBO vbo = buffers["../models/" + figure.filename];
    glColor3ub(figure.red, figure.green, figure.blue);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.index);
    glDrawElements(GL_TRIANGLES,
        vbo.n_index, // number of indexs' to draw
        GL_UNSIGNED_INT,  // index data type
        0); // not needed
    glColor3f(0,0,0);
}

void drawFigures(Group g) {
    glPushMatrix();
    for (auto& transform : g.transformations) {
        transform->applyTransform();
    }
    for (auto& modelFileName : g.models) {
        /*if (enableFrustum) {
            if (frustum.sphereInFrustum(modelFileName.second.centerPoint, modelFileName.second.radius) == Frustum::INSIDE)
                drawFigure(modelFileName.second);
        } else drawFigure(modelFileName.second);*/
        drawFigure(modelFileName.second);
    }
    for (auto& group : g.groups) {
        drawFigures(group);
    }
    glPopMatrix();
}

vector<string> split(string str, char separator) {
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

void read3Dfile(string filename) {
    VBO vbo = VBO();
    int slices, stacks;
    vector<float> points;
    vector<unsigned int> triangles;
    ifstream mfile(filename);
    float radius;
    string buffer;
    getline(mfile, buffer);
    vector<string> splitted_line = split(buffer, ' ');
    slices = stoi(splitted_line[0]);
    stacks = stof(splitted_line[1]);
    radius = stof(splitted_line[2]);
    for (auto i = 0; i < slices; i++) {
        getline(mfile, buffer);
        splitted_line = split(buffer, ' ');
        try {
            points.push_back(stof(splitted_line[0]));
            points.push_back(stof(splitted_line[1]));
            points.push_back(stof(splitted_line[2]));
        }
        catch (...) {
            cout << "Invalid line, number of arguments its different from 3!" << endl;
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo.vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);
    vbo.n_vertices = points.size();

    for (int i = 0; i < stacks; i++) {
        getline(mfile, buffer);
        splitted_line = split(buffer, ' ');
        try {
            triangles.push_back(stoi(splitted_line[0]));
            triangles.push_back(stoi(splitted_line[1]));
            triangles.push_back(stoi(splitted_line[2]));
        } 
        catch (...) {
            cout << i << endl;
        }
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triangles.size(), triangles.data(), GL_STATIC_DRAW);
    vbo.n_index = triangles.size();
    buffers[filename] = vbo; 
}

void readConfig(string file) {

    glEnableClientState(GL_VERTEX_ARRAY);
    file = "../config/" + file;
    XMLParser parser = XMLParser(file);
    groups = parser.parse();
    window_width = parser.window_width;
    window_height = parser.window_height;
    camera = parser.getCamera();
    unordered_set<string> files = parser.getModels();

    for (auto& filename : files) {
        string model = "../models/" + filename;
        read3Dfile(model);
    }
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio 
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera

	glLoadIdentity();
	gluLookAt(camera["position"].x * sinf(alpha * M_PI / 180.0) * cos(beta * M_PI / 180.0), camera["position"].y * sin(beta * M_PI / 180.0), camera["position"].z * cos(alpha * M_PI / 180.0) * cos(beta * M_PI / 180.0),
              camera["lookAt"].x , camera["lookAt"].y, camera["lookAt"].z,
              camera["up"].x, camera["up"].y, camera["up"].z);

    glScalef(x_scale, y_scale, z_scale);
    // put the drawing instructions here
    if (!see_axis) drawAxis();
    for (auto& g : groups) {
        drawFigures(g);
    }

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

    switch (c) {

        case '+':
            x_scale += 0.1f;
            y_scale += 0.1f;
            z_scale += 0.1f;
            break;

        case '-':
            if (x_scale >= 0.2f && y_scale >= 0.2f && z_scale >= 0.2f) {
                x_scale -= 0.1f;
                y_scale -= 0.1f;
                z_scale -= 0.1f;
            }
            break;

        case 'a': case 'A':
            alpha += 0.5f;
            break;

        case 'd': case 'D':
            alpha -= 0.5f;
            break;

        case 'f': case 'F':
            if (draw_mode) draw_mode = false;
            else draw_mode = true;
            glPolygonMode(GL_FRONT_AND_BACK, draw_mode ? GL_LINE : GL_FILL);
            break;

        case 'o': case 'O':
            if (see_axis) see_axis = false;
            else see_axis = true;
            break;

        case 'v': case 'V':
            enableFrustum = !enableFrustum;
            break;

        case 'c': case 'C':
            Translation::show_curves = !Translation::show_curves;
            break;

    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {

        case GLUT_KEY_PAGE_UP:
            boost = boost * 2;
            break;

        case GLUT_KEY_PAGE_DOWN:
            boost = boost / 2;
            break;

        case GLUT_KEY_UP:
            camera["position"].z += boost ;
            break;

        case GLUT_KEY_DOWN:
            camera["position"].z -= boost;
            break;

        case GLUT_KEY_RIGHT:
            camera["position"].x += boost ;
            break;

        case GLUT_KEY_LEFT:
            camera["position"].x -= boost;
            break;
    }
}

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN) {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON) {
            tracking = 1;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            tracking = 2;
        }
        else {
            tracking = 0;
        }
    }
    else if (state == GLUT_UP) {
        tracking = 0;
    }
}

void processMouseMotion(int xx, int yy) {
    int deltaX, deltaY;

    if (!tracking)
        return;

    if (tracking == 1 ) { // Movimento horizontal
        deltaX = xx - startX;
        alpha += deltaX * 0.25;
    }
    if (tracking == 2 ) { // Movimento vertical
        deltaY = yy - startY;
        beta += deltaY * 0.25;
        if (beta > 85.0)
            beta = 85.0;
        else if (beta < -85.0)
            beta = -85.0;
    }

    startX = xx;
    startY = yy;

    glutPostRedisplay();
}

int main (int argc, char **argv) {

    string filename;
    //filename = "box.xml";
    //filename = "sphere.xml";
    //filename = "cone.xml";
    //filename = "plane.xml";
    //filename = "torus.xml";
    //filename = "teapot.xml";

    //filename = "composed.xml"
    
    //filename = "snowman.xml";
    filename = "solar_system.xml";
    //filename = "test.xml";
    //filename = "test2.xml";

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("CG-TP");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    #ifndef __APPLE__
    glewInit();
    #endif

    // callback registration for keyboard processing
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    
    readConfig(filename);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();
    return 1;

}

