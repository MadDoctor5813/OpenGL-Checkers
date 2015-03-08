#pragma once

#include <GL\glew.h>

struct Vertex {
	struct Position {
		float x;
		float y;
	} pos;
	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;
};