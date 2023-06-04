#pragma once
#include <cstdlib>
#include <GL/glew.h>

class VBO {

	public:
		GLuint vertices;
		int n_vertices;
		GLuint index;
		int n_index;

		VBO();
};