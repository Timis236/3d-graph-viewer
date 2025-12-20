#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "components/World.hpp"
#include "components/Camera.hpp"
#include "components/Menu.hpp"

GLint winWidth = 800, winHeight = 800;
GLint isInMove = 0,
	  xbegin = 0,
	  ybegin = 0;

World myWorld;
Camera myCamera;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamera.setProjectionMatrix();
	myWorld.draw();
	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseActionFcn(int button, int state, int xMouse, int yMouse) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isInMove = 1;
		xbegin = xMouse;
		ybegin = yMouse;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		isInMove = 0;
	}
}

void mouseMotionFcn(GLint xMouse, GLint yMouse) {
    if (isInMove) {
        GLfloat thetaX = xbegin - xMouse;
        GLfloat thetaY = ybegin - yMouse;
        if (thetaX > 100) {
            thetaX = 100;
        }
        if (thetaX < -100) {
            thetaX = -100;
        }
        if (thetaY > 100) {
            thetaY = 100;
        }
        if (thetaY < -100) {
            thetaY = -100;
        }
        if (thetaY < 100 || thetaY > -100) {
            myCamera.rotate(0.0, 0.0, 1.0, thetaX*0.01);
        }
        if (thetaX < 100 || thetaX > -100) {
            myCamera.rotate(-myCamera.eye.y, myCamera.eye.x, 0.0, thetaY*0.01);
        }
        glutPostRedisplay();
    }
}

void mouseWheelFcn(int button, int dir, int xMouse, int yMouse) {
	if (dir > 0) {
		myCamera.eye.x += 2 * myCamera.eye.x / (pow(myCamera.eye.x, 2) + pow(myCamera.eye.y, 2) + pow(myCamera.eye.z, 2));
		myCamera.eye.y += 2 * myCamera.eye.y / (pow(myCamera.eye.x, 2) + pow(myCamera.eye.y, 2) + pow(myCamera.eye.z, 2));
		myCamera.eye.z += 2 * myCamera.eye.z / (pow(myCamera.eye.x, 2) + pow(myCamera.eye.y, 2) + pow(myCamera.eye.z, 2));
	} else {
		if (sqrt(pow(myCamera.eye.x, 2) + pow(myCamera.eye.y, 2) + pow(myCamera.eye.z, 2)) > 3) {
			myCamera.eye.x -= 2 * myCamera.eye.x / (pow(myCamera.eye.x, 2) + pow(myCamera.eye.y, 2) + pow(myCamera.eye.z, 2));
			myCamera.eye.y -= 2 * myCamera.eye.y / (pow(myCamera.eye.x, 2) + pow(myCamera.eye.y, 2) + pow(myCamera.eye.z, 2));
			myCamera.eye.z -= 2 * myCamera.eye.z / (pow(myCamera.eye.x, 2) + pow(myCamera.eye.y, 2) + pow(myCamera.eye.z, 2));
		}
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("3D Graph Viewer");
	init();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotionFcn);
	glutMouseFunc(mouseActionFcn);
	glutMouseWheelFunc(mouseWheelFcn);
	glutCreateMenu(mainMenu);
	menu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
