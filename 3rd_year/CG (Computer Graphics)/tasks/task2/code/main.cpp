#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

GLfloat x_trans = 0.0f, y_trans = 0.0f, z_trans = 0.0f, angle = 0.0f, y_scale = 1.0f;

void drawPyramid() {
	glBegin(GL_TRIANGLES);
	if (y_scale >= 0) {
		glColor3f(0.0f, 0.0f, 1.0f); // blue
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);

		glColor3f(1.0f, 0.0f, 0.0f); // red
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);

		glColor3f(0.0f, 1.0f, 0.0f); // green
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);

		glColor3f(1.0f, 1.0f, 0.0f); // yellow
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
	}
	else {
		glColor3f(0.0f, 0.0f, 1.0f); // blue
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);

		glColor3f(1.0f, 0.0f, 0.0f); // red
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);

		glColor3f(0.0f, 1.0f, 0.0f); // green
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);

		glColor3f(1.0f, 1.0f, 0.0f); // yellow
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);

	}

	//bottom
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);

	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd();
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put axis drawing in here

	glBegin(GL_LINES);
		// X Axis in Red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(- 100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,-100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();	
	

// put the geometric transformations here
	glTranslatef(x_trans, y_trans, z_trans);
	glScalef(1, y_scale, 1);
	glRotatef(angle, 0, 1, 0);

// put pyramid drawing instructions here
	drawPyramid();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void keyboardEvents(unsigned char key, int x, int y) {
	switch (key) {
		case 'W': case 'w':
			y_scale += 0.5f;
			break;
		case 'S': case 's':
			y_scale -= 0.5f;
			break;

		case 'A': case 'a':
			x_trans -= 0.1f;
			break;
		case 'D': case 'd':
			x_trans += 0.1f;
			break;
		
		case 'F': case 'f':
			z_trans -= 0.5f;
			break;
			case 'G': case 'g':
			z_trans += 0.5f;
			break;

		case 'E': case 'e':
			angle -= 5.0f;
			break;

		case 'Q': case 'q':
			angle += 5.0f;
			break;
	}
	glutPostRedisplay();
}




int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
		
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboardEvents);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
