#include <iostream>
#include <GL/glut.h>

static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void GLinitializer();
static void glutInitializer(int* argc, char** argv);

int main(int argc, char** argv) {

	glutInitializer(&argc, argv);

	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard);

	GLinitializer();

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

static void glutInitializer(int* argc, char** argv){

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Value Checker");

}

static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
		case 27: exit(EXIT_SUCCESS); break;
		default: break;
	}

}

static void on_display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_POINTS);
		glColor3f(0, 0.3, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(.75, 0, 0);
		glVertex3f(.75, .75, 0);
		glVertex3f(0, .75, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glColor3f(0.3, 0, 0);
		glVertex3f(-.1, -.1, 0);
		glVertex3f(-.85, -.1, 0);
		glVertex3f(-.85, -.85, 0);
		glVertex3f(-.1, -.85, 0);
	glEnd();

	glutSwapBuffers();
}

static void GLinitializer(){

	glClearColor(0.2, .2, .2, 0);
	glEnable(GL_DEPTH_TEST);

	GLfloat pointSize;
	GLfloat pointSizeRange[2];
	GLfloat lineWidth;
	GLfloat lineWidthRange[2];

	glPointSize(10);
	glLineWidth(3);

	glGetFloatv(GL_POINT_SIZE, &pointSize);
	glGetFloatv(GL_POINT_SIZE_RANGE, pointSizeRange);
	glGetFloatv(GL_LINE_WIDTH, &lineWidth);
	glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidthRange);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0xf0f0);

	printf("Current point size is: %f\n", pointSize);
	printf("Min point size is: %f\n", pointSizeRange[0]);
	printf("Max point size is: %f\n", pointSizeRange[1]);

	printf("Current line width is: %f\n", lineWidth);
	printf("Min line width is: %f\n", lineWidthRange[0]);
	printf("Max line width is: %f\n", lineWidthRange[1]);

}