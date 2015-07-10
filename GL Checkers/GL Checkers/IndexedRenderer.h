#pragma once

#include <GL\glew.h>
#include <map>
#include <vector>

#include "Engine\Vertex.h"

struct DrawBatch {
	std::vector<Vertex> vertexes;
	std::vector<int> indexes;
};

class IndexedRenderer {

public:
	IndexedRenderer();
	~IndexedRenderer();

	void draw(DrawBatch& batch, GLuint texture);
	void render();

private:
	GLuint vaoId = 0;
	GLuint vboId = 0;
	GLuint elementBufferId = 0;

	std::vector<Vertex> compiledVbo;
	std::vector<int> compiledElementBuffer; //this makes it so we don't have to copy around two giant vectors every render

	void initGLObjects();

	void compileVbo();
	void compileElementBuffer();

	std::map<GLuint, DrawBatch> batches;

};

