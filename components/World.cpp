#include "World.hpp"
#include "math.h"

using namespace std;

GLint row = 2 * MESH_DENSITY + 1;
GLint col = 2 * MESH_DENSITY + 1;
Point Pts[2 * MESH_DENSITY + 1][2 * MESH_DENSITY + 1];
float func_min, func_max;

void definePoints(int type) {
	float x, y, z;
	func_min = GRAPH_SIZE;
	func_max = -GRAPH_SIZE;

	for (int i = 0; i < 2 * MESH_DENSITY + 1; i++) {
		for (int j = 0; j < 2 * MESH_DENSITY + 1; j++) {
			x = (i * (float) GRAPH_SIZE / MESH_DENSITY) - GRAPH_SIZE;
			y = (j * (float) GRAPH_SIZE / MESH_DENSITY) - GRAPH_SIZE;

			int graph_type = type;
			if (graph_type == 1){
				z = 5*sin(sqrt(pow(x,2) + pow(y,2))); // change this to any other function of x and y to graph it
			}
			if (graph_type == 2){
				z = pow(x, 2) + pow(y, 2);
			}
			if (graph_type == 3){
				z = x + y;
			}
			if (graph_type == 4){
				z = x - y;
			}
			if (graph_type == 5){
				z = sqrt(x + y);
			}

			if (z < func_min) {
				func_min = z;
				if (func_min < -GRAPH_SIZE) {
					func_min = -GRAPH_SIZE;
				}
			}

			if (z > func_max) {
				func_max = z;
				if (func_max > GRAPH_SIZE) {
					func_max = GRAPH_SIZE;
				}
			}

			Pts[i][j].set(x, y, z);
		}
	}
}

World::World() {
	definePoints(1);
}

void World::setType(int type){
	definePoints(type);
	glutPostRedisplay();
}

void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void World::draw() {
	glColor3f(0.5, 0.5, 0.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int i = 0; i < row-1; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j < col; j++) {
			glColor3f(0.1 + 0.9*(((Pts[i][j].z + Pts[i + 1][j].z) / 2) - func_min) / (func_max - func_min), 0.1 + 0.9*(((Pts[i][j].z + Pts[i + 1][j].z) / 2) - func_min) / (func_max - func_min), 0.1 + 0.9*(((Pts[i][j].z + Pts[i + 1][j].z) / 2) - func_min) / (func_max - func_min));
			glVertex3f(Pts[i][j].x, Pts[i][j].y, Pts[i][j].z);
			glVertex3f(Pts[i + 1][j].x, Pts[i + 1][j].y, Pts[i + 1][j].z);
		}
		glEnd();
	}

	glColor3f(1.0, 0.0, 0.0);
	lineSegment(-GRAPH_SIZE, 0, 0, GRAPH_SIZE, 0, 0); /* x-axis in red */
 	glColor3f(0.0, 1.0, 0.0);
	lineSegment(0, -GRAPH_SIZE, 0, 0, GRAPH_SIZE, 0); /* y-axis in green */
	glColor3f(0.0, 0.0, 1.0);
	lineSegment(0, 0, -GRAPH_SIZE, 0, 0, GRAPH_SIZE); /* z-axis in blue */
}

