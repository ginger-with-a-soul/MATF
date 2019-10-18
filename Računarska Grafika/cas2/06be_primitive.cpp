#include <iostream>
#include <GL/glut.h>
#include <cmath>

#define NUM_OF_POINTS 10
#define RADIUS 0.5

static int primitive = GL_POINTS;

static void GLinitializer();
static void glutInitializer(int* argc, char** argv);
static void on_display();
static void on_keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){

	glutInitializer(&argc, argv);

	glutKeyboardFunc(on_keyboard);
	glutDisplayFunc(on_display);

	GLinitializer();

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

static void glutInitializer(int* argc, char** argv){

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Be Primitive!");

}

static void GLinitializer(){

	glClearColor(.4, .4, .4, 0);
	glPointSize(6);
	glLineWidth(3);

}

static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
		case '1': primitive = GL_POINTS; printf("Activated POINTS!\n"); break;
		case '2': primitive = GL_LINES; printf("Activated LINES!\n"); break;
		case '3': primitive = GL_LINE_STIPPLE; printf("Activated LINE STRIPPLE!\n"); break;
		case '4': primitive = GL_TRIANGLES; printf("Activated TRIANGLES!\n"); break;
		case '5': primitive = GL_TRIANGLE_STRIP; printf("Activated TRIANGLE STRIP!\n"); break;
		case '6': primitive = GL_LINE_LOOP; printf("Activated LINE LOOP!\n"); break;
		case '7': primitive = GL_QUAD_STRIP; printf("Activated QUAD STRIP!\n"); break;
		case '8': primitive = GL_QUADS; printf("Activated QUADS!\n"); break;
		case '9': primitive = GL_POLYGON; printf("Activated POLYGON!\n"); break;
		case '0': primitive = GL_TRIANGLE_FAN; printf("Activated TRIANGLE FAN!\n"); break;
		case 'd': glDisable(GL_CULL_FACE); printf("Deactivated culling!\n"); break;
		case 'f': glCullFace(GL_FRONT); glEnable(GL_CULL_FACE); printf("Activated front culling!\n"); break;
		case 'b': glCullFace(GL_BACK); glEnable(GL_CULL_FACE); printf("Activated back culling!\n"); break;
		default: break;
	}

	glutPostRedisplay();

}

static void on_display(){
	glClear(GL_DEPTH_BITS | GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
		glColor3f(0.4, 0, 0);
		glVertex2f(0, 0);
		for(int i = 0; i < NUM_OF_POINTS; i++){
			glVertex2f(RADIUS * cos(2 * i * M_PI / NUM_OF_POINTS), RADIUS * sin(2 * i * M_PI / NUM_OF_POINTS));
		}
	glEnd();

	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(primitive);
		glColor3f(0, 0.4, 0);
		glVertex2f(0, 0);
		for(int i = 0; i < NUM_OF_POINTS; i++){
			glVertex2f(RADIUS * cos(2 * i * M_PI / NUM_OF_POINTS), RADIUS * sin(2 * i * M_PI / NUM_OF_POINTS));
		}
	glEnd();


	glutSwapBuffers();
}