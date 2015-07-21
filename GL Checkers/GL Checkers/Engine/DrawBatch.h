#pragma once

#include <vector>
#include <GL/glew.h>
#include "Engine\Vertex.h"

struct DrawBatch {
	std::vector<Vertex> vertexes;
	std::vector<GLuint> indexes;

	GLuint texture;
};