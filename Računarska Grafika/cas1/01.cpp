#include <iostream>
#include <GL/glut.h>

static void on_display();

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("01");

	glClearColor(0.75, 0.75, 0.75, 0);

	glutDisplayFunc(on_display);

	glutMainLoop();

    return 0;
}

void on_display(){

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
		glColor3f(0, 0, 1);
			glVertex2f(-0.5, -0.5);
			glVertex2f(0.5, -0.5);
			glVertex2f(0.5, 0.5);
			glVertex2f(-0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex2f(0.9, 0.9);
		glVertex2f(0.9, 0.5);
		glVertex2f(0.5, 0.9);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0, 1, 0);
		glVertex2f(-0.9, -0.9);
		glVertex2f(-0.5, -0.9);
		glVertex2f(-0.9, -0.5);
	glEnd();

	glutSwapBuffers();
}