#include "IndexedRenderer.h"
#include "ShaderProgram.h"
#include "App.h"

#include <iostream>
#include <algorithm>


IndexedRenderer::IndexedRenderer() {

}


IndexedRenderer::~IndexedRenderer() {

}

void IndexedRenderer::init(App& appRef) {
	initGLObjects();
	initShaders(appRef);
}

void IndexedRenderer::initGLObjects() {
	//generate the needed GL objects
	glGenVertexArrays(1, &vaoId);
	//create VAO state
	glBindVertexArray(vaoId);
	//bind buffers
	glGenBuffers(1, &vboId);
	glGenBuffers(1, &iboId); 
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	//Enable arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//Set position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	//Set texture coord attrib pointer
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	//Set color attrib pointer
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//Cleanup
	glBindVertexArray(0);
}

void IndexedRenderer::initShaders(App& appRef) {
	ShaderProgram& shader = appRef.getShaderManager().getShader("spriteShading");
	camTransformLoc = glGetUniformLocation(shader.getProgram(), "camTransform");
	textureLoc = glGetUniformLocation(shader.getProgram(), "spriteTexture");
	glActiveTexture(GL_TEXTURE0);
}

void IndexedRenderer::draw(DrawBatch& newBatch, int depth, int texture) {
	if (batches.count(depth) == 0) { //if there is no depth batch
		batches.emplace(depth, std::map<GLuint, DrawBatch>()); //make a new one
	}
	if (batches.at(depth).count(texture) == 0) { //if there is no texture batch
		batches.at(depth).emplace(texture, DrawBatch()); //make one
	}
	DrawBatch& oldBatch = batches.at(depth).at(texture);
	for (auto& index : newBatch.indexes) {
		index += oldBatch.vertexes.size(); //update indexes to work after appending
	}
	oldBatch.vertexes.insert(oldBatch.vertexes.end(), newBatch.vertexes.begin(), newBatch.vertexes.end());
	oldBatch.indexes.insert(oldBatch.indexes.end(), newBatch.indexes.begin(), newBatch.indexes.end()); //append data
}

void IndexedRenderer::render(App& appRef) {
	appRef.getShaderManager().getShader("spriteShading").enable();
	glActiveTexture(GL_TEXTURE0);
	//upload uniform data
	glUniformMatrix4fv(camTransformLoc, 1, GL_FALSE, &(appRef.getCamera().getMatrix()[0][0]));
	glUniform1i(textureLoc, 0);
	//compile data for buffers
	compileVbo();
	compileIbo();
	glBindVertexArray(vaoId);
	//upload buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * compiledVbo.size(), compiledVbo.data(), GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * compiledIbo.size(), compiledIbo.data(), GL_STREAM_DRAW);
	int drawOffset = 0;
	int baseVertex = 0;
	int count = 0;
	for (auto depthBatch : batches) {
		for (auto textureBatch : depthBatch.second) {
			count += textureBatch.second.indexes.size();
			makeDrawCall(count, drawOffset, baseVertex, textureBatch.first);
			drawOffset += count;
			count = 0;
			baseVertex += textureBatch.second.vertexes.size();
		}
	}
	batches.clear();
	glBindVertexArray(0);
}

void IndexedRenderer::makeDrawCall(int count, int offset, int baseVertex, GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * offset), baseVertex);
}

void IndexedRenderer::compileVbo() {
	compiledVbo.clear();
	for (auto depthBatch : batches) {
		for (auto textureBatch : depthBatch.second) {
			compiledVbo.insert(compiledVbo.end(), textureBatch.second.vertexes.begin(), textureBatch.second.vertexes.end());
		}
	}
	
}

void IndexedRenderer::compileIbo() {
	compiledIbo.clear();
	for (auto depthBatch : batches) {
		for (auto textureBatch : depthBatch.second) {
			compiledIbo.insert(compiledIbo.end(), textureBatch.second.indexes.begin(), textureBatch.second.indexes.end());
		}
	}
}