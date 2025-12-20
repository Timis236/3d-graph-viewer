#ifndef CWORLD_HPP
#define CWORLD_HPP

#include <iostream>
#include <list>
#include <vector>
#include "Vector.hpp"

// this determines how dense the mesh quads are and how big the actual graph is, respectively
#define MESH_DENSITY 100
#define GRAPH_SIZE 10

class World {

public:
	World();
	void setType(int type);
	void draw();   /* draw all objects in the world */
};

#endif
