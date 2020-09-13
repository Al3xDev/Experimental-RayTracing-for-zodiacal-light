#include "mesh.h"
#include <stdlib.h>
#include <stdint.h>

mesh* mesh_create( int size, int nsize, void *data)
{
	mesh *mh = (mesh*) malloc( sizeof( mesh));

	mh->count = nsize;

	glGenVertexArrays( 1, &(mh->vao));
	glBindVertexArray( mh->vao);

	glGenBuffers( 1, &(mh->vbo));
	glBindBuffer( GL_ARRAY_BUFFER, mh->vbo);
	glBufferData( GL_ARRAY_BUFFER, size*nsize*sizeof( GL_FLOAT) , (GLvoid*) data, GL_STATIC_DRAW);

	glVertexAttribPointer( 0, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray( 0);

	glBindVertexArray( 0);

	return mh;
}


void mesh_draw_points( mesh *mh)
{
	glBindVertexArray( mh->vao);
	glDrawArrays( GL_POINTS, 0, mh->count);
	glBindVertexArray( 0);
}

void mesh_destroy( mesh *mh)
{
	glDeleteVertexArrays( 1, &(mh->vao));
	glDeleteBuffers( 1, &(mh->vbo));

	free( (void*)mh);
}
