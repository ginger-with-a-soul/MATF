#include <iostream>
#include <GL/glut.h>

static int windowHeight, windowWidth;

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void GLinitializer();
static void glutInitializer(int* argc, char** argv);

int main(int argc, char** argv){

	glutInitializer(&argc, argv);
	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard);
	glutReshapeFunc(on_reshape);
	GLinitializer();

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

static void glutInitializer(int* argc, char** argv){

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("3D Cube");

}

static void GLinitializer(){

	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2);

}

static void on_reshape(int width, int height){

	windowHeight = height;
	windowWidth = width;

}

static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
		case 27: exit(EXIT_SUCCESS); break;
		default: break;
	}

}

static void on_display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, windowWidth, windowHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, windowWidth / (float)windowHeight, 1, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

	glColor3f(0.4, 0, 0);
	glTranslatef(0, 0.5, 0.5);
	glScalef(1, 2, 1);
	glutWireCube(1);

	glutSwapBuffers();

}