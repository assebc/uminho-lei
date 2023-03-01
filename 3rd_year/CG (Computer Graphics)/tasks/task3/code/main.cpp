#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

GLenum drawMode = GL_FILL;
float alpha = 0.0f;
float beta = 0.0f;
float radius = 9.0f;

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


void drawCylinder(float radius, float height, int slices) {

    // Set the angle increment for each slice
    float angle_incr = 2 * M_PI / slices;

    // Draw top cap of the cylinder
    glBegin(GL_TRIANGLE_FAN);
    // Set the color to blue
    glColor3f(0.0f, 0.0f, 1.0f);
    // Set the center vertex of the fan
    glVertex3f(0.0f, height / 2.0, 0.0f);
    // Draw vertices around the circle
    for (int i = 0; i <= slices; i++) {
        float angle = i * angle_incr;
        float px = radius * cosf(angle);
        float pz = radius * sinf(angle);
        glVertex3f(px, height / 2.0, pz);
    }
    glEnd();

    // Set the color to red
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    // Draw each slice of the cylinder
    for (int i = 0; i <= slices; i++) {
        float angle = i * angle_incr;
        float angle2;
        if (i == slices) angle2 = 0.0f;
        else angle2 = (i+1) * angle_incr;

        float px = radius * cosf(angle);
        float px_aux = radius * cosf(angle2);
        float pz = radius * sinf(angle);
        float pz_aux = radius * sinf(angle2);

        // Draw top vertex
        glVertex3f(px, height / 2.0, pz);
        glVertex3f(px, -height / 2.0, pz);
        glVertex3f(px_aux, -height / 2.0, pz_aux);

        glVertex3f(px, height / 2.0, pz);
        glVertex3f(px_aux, -height / 2.0, pz_aux);
        glVertex3f(px_aux, height / 2.0, pz_aux);

        glEnd();
    }

    // Draw bottom cap of the cylinder
    glBegin(GL_TRIANGLE_FAN);
    // Set the color to blue
    glColor3f(0.0f, 0.0f, 1.0f);
    // Set the center vertex of the fan
    glVertex3f(0.0f, -height / 2.0, 0.0f);
    // Draw vertices around the circle (in reverse order)
    for (int i = slices; i >= 0; i--) {
        float angle = i * angle_incr;
        float px = radius * cosf(angle);
        float pz = radius * sinf(angle);
        glVertex3f(px, -height / 2.0, pz);
    }
    glEnd();

    // Enable face culling
    glEnable(GL_CULL_FACE);
    // Set culling mode
    glCullFace(GL_FRONT);
}

void drawAxis() {
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();

    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();

    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(radius * cosf(beta) * sinf(alpha), radius * sinf(beta), radius * cosf(beta) * cosf(alpha),
        0.0, 0.0, 0.0,
        0.0f, 1.0f, 0.0f);

    glPolygonMode(GL_FRONT_AND_BACK, drawMode);
    if (drawMode == GL_POINT) {
        glPointSize(10.0F);
    }
    if (drawMode == GL_LINE) {
        glLineWidth(5.0f);
    }

    drawAxis();
    drawCylinder(1, 2, 10);

    // End of frame
    glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
    switch (c) {
        // Move camera up
    case 'w': case 'W':
        beta += 0.1f;
        break;
        // Move camera down
    case 's': case 'S':
        beta -= 0.1f;
        break;

    case 'a': case 'A':
        alpha += 0.1f;
        break;

    case 'd': case 'D':
        alpha -= 0.1f;
        break;

    case 'p': case 'P':
        drawMode = GL_POINT;
        break;
    case 'l': case ' L':
        drawMode = GL_LINE;
        break;
    case 'f': case 'F':
        drawMode = GL_FILL;
        break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
}



int main(int argc, char** argv) {

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}