#include "../include/VBO.h"

VBO::VBO() {
	n_vertices = 0;
	n_index = 0;
	glGenBuffers(1, &vertices);
	glGenBuffers(1, &index);
}