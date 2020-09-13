#include <iostream>
#include <stdint.h>
#include <unistd.h>

#define GLEW_STATIC
    #include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vec.h"
#include "shader.h"
#include "texture.h"
#include "bitmap.h"
#include "mesh.h"

#include <math.h>

using namespace std;

float PI = 3.141592654;
float D = 1.496e8;
float Rp = 6371;
float dd = 0.7304687e5;

typedef struct sphere_s
{
    float r;
    vec3f pos;
    vec3f color;
} sphere;

typedef struct light_s
{
    vec3f pos;
    vec3f color;
} light;

typedef struct ray_tracing_s
{
    vec3f const base_camera_pos = { .x = 0, .y = 0, .z = 1};
    vec3f const base_camera_dir = { .x = 0, .y = 1, .z = 0};
    vec3f const base_camera_up = { .x = 1, .y = 0, .z = 0};
    vec3f const base_camera_rig = { .x = 1, .y = 0, .z = 0};

    vec3f const clear_color = { .x = 0, .y = 0, .z = 0};

    int viewport_width, viewport_height;

    float half_h = 0.5;

} ray_tracing;


vec3f* gen_viewport_points( int w_size)
{
    vec3f *viewport_p = new vec3f [w_size*w_size];
    for( int i=0; i<w_size; ++i)
    {
        for( int j=0; j<w_size; ++j)
        {
            viewport_p[ i + j*w_size].x = float(i)/w_size*2.0 - 1.0;
            viewport_p[ i + j*w_size].y = float(j)/w_size*2.0 - 1.0;
            viewport_p[ i + j*w_size].z = i;
        }
    }
    return viewport_p;
}


int main()
{

    GLFWwindow *window = NULL;
    int window_size = 1000;

    // init glfw
    int ret = glfwInit();

    if( ret != GL_TRUE)
    {
        std::cerr<<"GLFW init error\n";
        return 0;
    }

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    window = glfwCreateWindow( window_size, window_size, "ZL - RAY TRACING", NULL, NULL);

    glfwMakeContextCurrent( window);

    glewExperimental = GL_TRUE;
    if( glewInit() != GLEW_OK)
    {
        std::cerr<<"GLEW init error\n";
        return 0;
    }

    glViewport( 0, 0, window_size, window_size);
    glEnable( GL_DEPTH_TEST);
    glViewport( 0, 0, window_size, window_size);

    glClearColor( 0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec3f *viewport_points = gen_viewport_points( window_size);

    mesh *mh = mesh_create( 3, window_size*window_size, (void*)viewport_points);

    shader sh = shader_create();
    shader sh_vf[2];
    sh_vf[0] = shader_load( "vertexShader.glsl", GL_VERTEX_SHADER);
    sh_vf[1] = shader_load( "fragmentShader.glsl", GL_FRAGMENT_SHADER);
    shader_link( sh, sh_vf, 2);

    vec3f sun;
    float alpha = 140;
    sun.x = cos( alpha*PI/180)*D;
    sun.y = 0;
    sun.z = sin( alpha*PI/180)*D;

    float Dmax = 1.0e9;
    float steps = 10000;

    float sun_intens = 1.0e27;

        {
            shader_use( sh);
            shader_set_int( sh, "viewport_size", window_size);
            shader_set_vec3f( sh, "sun_pos", &sun);
            shader_set_float( sh, "sun_intens", sun_intens);
            shader_set_float( sh, "steps", steps);
            shader_set_float( sh, "Dmax", Dmax);

            mesh_draw_points( mh);

            glfwSwapBuffers( window);

        }

    sleep(100);
    return 0;
}
