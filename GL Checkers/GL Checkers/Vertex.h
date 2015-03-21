#pragma once

#include <GL\glew.h>


struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct TexCoord {
	float u;
	float v;
};

struct Vertex {
	Position pos;
	Color color;
	TexCoord texCoord;

};