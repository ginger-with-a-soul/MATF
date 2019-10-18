#include <iostream>
#include <GL/glut.h>

static void in_ray();
static void out_ray();
static void middle_ray();
static void triangle();
static void on_display();

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Dark Side of the Moon");

	glClearColor(0, 0, 0, 0);
	glutDisplayFunc(on_display);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void on_display(){

	glClear(GL_COLOR_BUFFER_BIT);

	in_ray();
	out_ray();
	triangle();
	middle_ray();

	glutSwapBuffers();

}

static void in_ray(){

	glLineWidth(2);

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex2f(-1, -0.2);
		glVertex2f(0, 0.2);
	glEnd();
}

static void out_ray(){

	for(int i = 0; i < 6; i++){
		switch(i){
			case 0: glColor3f(0.6, 0.2, 1); break;
			case 1: glColor3f(0, 0.8, 0.8); break;
			case 2: glColor3f(0.3, 1, 0); break;
			case 3: glColor3f(0.8, 0.8, 0); break;
			case 4: glColor3f(1, 0.5, 0); break;
			case 5: glColor3f(0.9, 0, 0); break;
			default: break;
		}

		glBegin(GL_TRIANGLES);
			glVertex2f(0, 0.2);
			glVertex2f(1, -0.2);
			glVertex2f(1, -0.5 + i * 0.05);
		glEnd();
	}

}

static void middle_ray(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 1);
		glVertex2f(-0.2, 0.121);
		glColor3f(0.3, .3, .3);
		glVertex2f(0.19, 0.121);
		glVertex2f(0.2655, 0.008);
	glEnd();

}

static void triangle(){

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
		glColor3f(0.08, 0.08, 0.08);
		glVertex2f(0, 0.41);
		glVertex2f(-.4, -.19);
		glVertex2f(.4, -.19);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_TRIANGLES);
		glColor3f(.9, .9, .9);
	glVertex2f(0, 0.41);
	glVertex2f(-.4, -.19);
	glVertex2f(.4, -.19);
	glEnd();

}