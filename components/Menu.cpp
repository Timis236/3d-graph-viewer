#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

extern GLint csType;
extern GLint transType, xbegin;
extern World myWorld;
extern Camera myCamera;

void menu() {
    glutCreateMenu(mainMenu);

    glutAddMenuEntry("Reset Camera", 0);
    glutAddMenuEntry("z = 5*sin(sqrt(x^2 + y^2))", 1);
    glutAddMenuEntry("z = x^2 + y^2", 2);
    glutAddMenuEntry("z = x + y", 3);
    glutAddMenuEntry("z = x - y", 4);
    glutAddMenuEntry("z = sqrt(x + y)", 5);
    glutAddMenuEntry("Zoom In", 6);
    glutAddMenuEntry("Zoom Out", 7);
    glutAddMenuEntry("Quit", 8);
}

void mainMenu(int option) {
	switch (option){
		case 0:
			//myWorld.reset();
			myCamera.setDefaultCamera();
			break;
		case 1:
			myWorld.setType(1);
			break;
		case 2:
			myWorld.setType(2);
			break;
		case 3:
			myWorld.setType(3);
			break;
		case 4:
			myWorld.setType(4);
			break;
		case 5:
			myWorld.setType(5);
			break;
        case 6:
            // Zoom In
            {
                float length = sqrt(myCamera.viewNorm.x * myCamera.viewNorm.x +
                                    myCamera.viewNorm.y * myCamera.viewNorm.y +
                                    myCamera.viewNorm.z * myCamera.viewNorm.z);

                if (length != 0.0f) {
                    float factor = 0.8f / length;  // Adjust the factor as needed
                    myCamera.eye.x += factor * myCamera.viewNorm.x;
                    myCamera.eye.y += factor * myCamera.viewNorm.y;
                    myCamera.eye.z += factor * myCamera.viewNorm.z;
                }
            }
            break;
        case 7:
            // Zoom Out
            {
                float length = sqrt(myCamera.viewNorm.x * myCamera.viewNorm.x +
                                    myCamera.viewNorm.y * myCamera.viewNorm.y +
                                    myCamera.viewNorm.z * myCamera.viewNorm.z);

                if (length != 0.0f) {
                    float factor = 0.8f / length;
                    myCamera.eye.x -= factor * myCamera.viewNorm.x;
                    myCamera.eye.y -= factor * myCamera.viewNorm.y;
                    myCamera.eye.z -= factor * myCamera.viewNorm.z;
                }
            }
            break;
        case 8:
			exit(0);
			break;
	}
	myCamera.setProjectionMatrix();  // Update the projection matrix after zooming
	glutPostRedisplay();
}
