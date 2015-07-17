#pragma once

#include <GL\glew.h>
#include <map>
#include <vector>

#include "Engine\Vertex.h"
#include "App.h"

struct DrawBatch {
	std::vector<Vertex> vertexes;
	std::vector<GLuint> indexes;

	GLuint texture;
};

class IndexedRenderer {

public:
	IndexedRenderer();
	~IndexedRenderer();

	void init(App& appRef);
	void draw(DrawBatch& batch, int depth);
	void render(App& appRef);

private:
	GLuint vaoId = 0;
	GLuint vboId = 0;
	GLuint iboId = 0;

	GLint camTransformLoc;
	GLint textureLoc;

	std::vector<Vertex> compiledVbo;
	std::vector<GLuint> compiledIbo; //this makes it so we don't have to copy around two giant vectors every render

	void initGLObjects();
	void initShaders(App& appRef);

	void sortBatches();
	void compileVbo();
	void compileIbo();
	
	std::map<int, std::vector<DrawBatch>> batches;
};

