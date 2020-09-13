#define GLEW_STATIC
#include <GL/glew.h>

#include "vec.h"

typedef GLuint shader;

shader shader_create();

shader shader_load( char*, GLenum);

void shader_link( shader, shader*, int);

void shader_use( shader);

void shader_destroy( shader);

void shader_set_float( shader, char*, float);

void shader_set_int( shader, char*, int);

void shader_set_double( shader, char*,  double);

void shader_set_vec3f( shader, char*,  vec3f*);

void shader_set_vec3d( shader, char*,  vec3d*);


