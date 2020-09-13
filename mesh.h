#ifndef MESH_H
#define MESH_H

#include "vec.h"
#define GLEW_STATIC
#include <GL/glew.h>

typedef struct mesh_s
{
	GLuint vao, vbo;
	int count;

} mesh;


mesh* mesh_create( int, int, void*);

void mesh_draw_points( mesh*);

void mesh_destroy( mesh*);
#endif
