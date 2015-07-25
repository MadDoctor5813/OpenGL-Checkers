#pragma once

#include <GL\glew.h>
#include <map>
#include <vector>

#include "Engine\Vertex.h"
#include "DrawBatch.h"

class App;

class IndexedRenderer {

public:
	IndexedRenderer();
	~IndexedRenderer();

	void init(App& appRef);
	void draw(DrawBatch& batch, int depth, int texture);
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

	void compileVbo();
	void compileIbo();

	void makeDrawCall(int count, int offset, int baseVertex, GLuint texture);
	
	std::map<int, std::map<GLuint, DrawBatch>> batches;
};

