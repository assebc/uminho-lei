#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <time.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
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

void drawTorus() {
	glColor3f(1.0f, 0.0f, 1.0f);
	glPushMatrix();
	glutSolidTorus(0.5f, 1.5f, 10, 10);
	glPopMatrix();
}

void drawCowboys(int nr_cowboys, float radius) {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	const float delta = (2 * M_PI) / nr_cowboys;
	float alpha = currentTime * delta;
	glColor3f(0, 0, 1);
	for (int i = 0; i < nr_cowboys; i++) {
		float x = radius * sin(alpha);
		float z = radius * cos(alpha);
		glPushMatrix();
		glTranslatef(x, 0.8, z);
		glRotatef((alpha / M_PI) * 180 - 90, 0, 1, 0);
		glutSolidTeapot(1);
		glPopMatrix();
		alpha += delta;
		if (alpha > (2 * M_PI))
			alpha -= (2 * M_PI);
	}
}

void drawIndian(int nr_indians, float radius) {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	const float delta = (2 * M_PI) / nr_indians;
	float alpha = currentTime * delta;
	glColor3f(1, 0, 0);
	for (int i = 0; i < nr_indians; i++) {
		float x = radius * sin(alpha);
		float z = radius * cos(alpha);
		glPushMatrix();
		glTranslatef(x, 0.8, z);
		glRotatef((alpha / M_PI) * 180, 0, 1, 0);
		glutSolidTeapot(1);
		glPopMatrix();
		alpha += delta;
		if (alpha > (2 * M_PI))
			alpha -= (2 * M_PI);
	}
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
	glVertex3f(100.0f, 0, -100.0f);
	glVertex3f(-100.0f, 0, -100.0f);
	glVertex3f(-100.0f, 0, 100.0f);

	glVertex3f(100.0f, 0, -100.0f);
	glVertex3f(-100.0f, 0, 100.0f);
	glVertex3f(100.0f, 0, 100.0f);
	glEnd();

	// put code to draw scene in here

	drawTorus();
	drawCowboys(8, 5);
	drawIndian(20, 20);

	for (int i = 0; i < 300; i++) {
		glPushMatrix();
		double posx = 0, posz = 0;
		while (pow(posx, 2) + pow(posz, 2) < pow(30, 2)) {
			posx = (rand() % (30 * 4)) - (30 * 2);
			posz = (rand() % (30 * 4)) - (30 * 2);
		}
		glTranslated(posx, 0, posz);
		glRotated(-90, 1, 0, 0);
		glColor3ub(102, 62, 36);
		glutSolidCone(0.5, 2, 10, 10);
		glTranslated(0, 0, 2);
		glColor3ub(0, 255, 0);
		glutSolidCone(2, 4, 10, 10);
		glPopMatrix();
	}

	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

	// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
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

	spherical2Cartesian();

	printInfo();

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
