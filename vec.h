#ifndef VEC_H
#define VEC_H

#include <stdint.h>
#include <math.h>

typedef struct vec2i16_s
{
	int16_t x,y;
} vec2i16;

typedef struct vec2f_s
{
    float x,y;
} vec2f;

typedef struct vec3i_s
{
	int32_t x,y,z;
} vec3i;


typedef struct vec3f_s
{
	float x,y,z;
} vec3f;


typedef struct vec3d_s
{
	double x,y,z;
} vec3d;

float dot( vec3f*, vec3f*);

void cross( vec3f*, vec3f*, vec3f*);

void normalize( vec3f*);

float length( vec3f*);

float distance( vec3f*, vec3f*);
#endif // VEC_H
