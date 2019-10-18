#include <iostream>
#include <GL/glut.h>
#include <ctime>

#define TIMER_ID 0
#define TIMER_INTERVAL 10

static void on_timer(int val);
static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void rand_pos();
static void rand_speed();

static float size = 0.2;
static float xCurr = 0;
static float yCurr = 0;
static float vxCurr = 0;
static float vyCurr = 0;
static  bool animationOngoing = false;


int main(int argc, char** argv) {

	//std::cin >> size;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Screen Bouncer");

	glClearColor(0.1, 0.1, 0.1, 0);
	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard);
	glEnable(GL_DEPTH_TEST);

	srand(time(NULL));

	rand_pos();
	rand_speed();

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

static void rand_pos(){

	xCurr = -(1 - size + 0.04 / 2) + (2 - size) * rand() / (float) RAND_MAX;
	yCurr = -(1 - size + 0.04 / 2) + (2 - size) * rand() / (float) RAND_MAX;
}

static void rand_speed(){

	vxCurr = rand() / (float) RAND_MAX * size - size / 2;
	vyCurr = rand() / (float) RAND_MAX * size - size / 2;

}

static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
		case 27: case 'q' : case 'Q': exit(EXIT_SUCCESS); break;
		case 32:
			if(!animationOngoing){
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
				animationOngoing != animationOngoing;
			}
			break;
		case 's': case 'S': animationOngoing != animationOngoing; break;
		case 'v': case 'V': rand_speed(); break;
		case 'p': case 'P': rand_pos(); break;
		case 'r': case 'R': rand_speed(); rand_pos(); break;
		default: break;
	}

}

static void on_display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK,  GL_LINE);
	glLineWidth(9);
	glBegin(GL_POLYGON);
		glColor3f(.9, .05, .9);
		glVertex2f(-1, 1);
		glVertex2f(-1, -1);
		glVertex2f(1, -1);
		glVertex2f(1, 1);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
		glColor3f(.02, .3, .5);
		glVertex2f(xCurr - (size / 2), yCurr + size / 2);
		glVertex2f(xCurr -(size / 2), yCurr - (size / 2));
		glVertex2f(xCurr + size / 2, yCurr - (size / 2));
		glVertex2f(xCurr + size / 2, yCurr + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(1, 0, 1);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
		glVertex3f(xCurr, yCurr);
	glEnd();

	glutSwapBuffers();
}

static void on_timer(int val){

	if(val != TIMER_ID){
		return;
	}

	xCurr += vxCurr;
	if(xCurr <= -(1 - size / 2) + 0.04 || xCurr >= 1 - size / 2 - 0.04){
		vxCurr *= -1;
	}

	yCurr += vyCurr;
	if(yCurr <= -(1 - size / 2) + 0.04 || yCurr >= 1 - size / 2 - 0.04){
		vyCurr *= -1;
	}

	glutPostRedisplay();

	if(animationOngoing){
		glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
	}

}