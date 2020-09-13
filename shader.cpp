#include "shader.h"
#include <stdio.h>


shader shader_create()
{
	return glCreateProgram();
}

shader shader_load( char *file_name, GLenum shader_type)
{
	FILE *file = fopen( file_name, "rb");

	if( file == NULL)
	{
		printf("shader_load error: open file\n");
		return 0;
	}

	char *source;
	long source_size;

	fseek( file, 0, SEEK_END);
	source_size = ftell( file);
	fseek( file, 0, SEEK_SET);

	source = (char*) malloc( source_size + 1);
	source[ source_size + 1] = 0;

	fread( source, 1, source_size, file);

	shader part_shader = glCreateShader( shader_type);

	glShaderSource( part_shader, 1, (GLchar**) &source, NULL);

	glCompileShader( part_shader);

	GLint result;
	glGetShaderiv( part_shader, GL_COMPILE_STATUS, &result);

	if( !result)
	{
		GLint log_len;
		glGetShaderiv( part_shader, GL_INFO_LOG_LENGTH, &log_len);

		if( log_len > 0)
		{
			char *log = ( char*) malloc( log_len);
			GLsizei written;
			glGetShaderInfoLog( part_shader, log_len, &written, log);
			printf("shader_load error: compile shader file: %s\n\n%s\n\n", file_name, log);

			free( log);
		}

		return 0;
	}

	return part_shader;
}


void shader_link( shader program, shader *shaders, int shaders_size)
{
	for( int i = 0; i < shaders_size; ++i)
	{
		glAttachShader( program, shaders[i]);
	}

	glLinkProgram( program);

	GLint result;
	glGetShaderiv( program, GL_LINK_STATUS, &result);

	if( !result)
	{
		GLint log_len;
		glGetShaderiv( program, GL_INFO_LOG_LENGTH, &log_len);

		if( log_len > 0)
		{
			char *log = ( char*) malloc( log_len);
			GLsizei written;
			glGetShaderInfoLog( program, log_len, &written, log);
			printf("shader_load error: link program: \n%s\n\n", log);

			free( log);
		}

        return;
	}

	for( int i = 0; i < shaders_size; ++i)
	{
		glDeleteShader( shaders[i]);
	}

}


void shader_use( shader program)
{
	glUseProgram( program);
}

void shader_destroy( shader program)
{
	glDeleteProgram( program);

}

void shader_set_int( shader program, char *uniform_name, int val)
{
    glUniform1i(glGetUniformLocation( program, uniform_name), val);
}

void shader_set_float( shader program, char *uniform_name, float val)
{
	glUniform1f( glGetUniformLocation( program, uniform_name), val);
}

void shader_set_double( shader program, char *uniform_name,  double val)
{
	glUniform1d( glGetUniformLocation( program, uniform_name), val);
}

void shader_set_vec3f( shader program, char *uniform_name,  vec3f *vec)
{
	glUniform3f( glGetUniformLocation( program, uniform_name),vec->x, vec->y, vec->z);
}

void shader_set_vec3d( shader program, char *uniform_name,  vec3d *vec)
{
	glUniform3d( glGetUniformLocation( program, uniform_name), vec->x, vec->y, vec->z);
}
