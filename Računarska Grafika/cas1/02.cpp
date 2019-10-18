#include <iostream>
#include <GL/glut.h>

static void on_display();

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The Flag of Serbia");

	glClearColor(0.5, 0.5, 0.5, 0);

	glutDisplayFunc(on_display);
	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void on_display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex3f(-0.9, -0.9, 0);
		glVertex3f(0.9, -0.9, 0);
		glVertex3f(0.9, 0.9, 0);
		glVertex3f(-0.9, 0.9, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0, 0, 1);
		glVertex3f(-0.9, -0.3, 0.1);
		glVertex3f(0.9, -0.3, 0.1);
		glVertex3f(0.9, 0.9, 0.1);
		glVertex3f(-0.9, 0.9, 0.1);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(1, 0, 0);
		glVertex3f(-0.9, 0.3, 0.2);
		glVertex3f(0.9, 0.3, 0.2);
		glVertex3f(0.9, 0.9, 0.2);
		glVertex3f(-0.9, 0.9, 0.2);
	glEnd();

	glutSwapBuffers();
}