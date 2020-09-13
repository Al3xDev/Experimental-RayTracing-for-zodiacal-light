#version 450 core
layout (location = 0) in vec3 viewport_point;
out vec3 pos;

uniform int viewport_size;

void main()
{
    pos = viewport_point;
    gl_Position = vec4( viewport_point.x, viewport_point.y, 0, 1.0);
}
