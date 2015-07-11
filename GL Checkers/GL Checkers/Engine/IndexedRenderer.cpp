#include "IndexedRenderer.h"

#include <iostream>


IndexedRenderer::IndexedRenderer() {

}


IndexedRenderer::~IndexedRenderer() {

}

void IndexedRenderer::init() {
	initGLObjects();
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

void IndexedRenderer::draw(DrawBatch& newBatch, GLuint texture) {
	//if the texture isn't already being batched, make a new batch
	if (batches.count(texture) == 0) {
		batches.emplace(texture, DrawBatch());
	} 
	DrawBatch& batch = batches.at(texture);
	//add vertices for this call to the batch
	batch.vertexes.insert(batch.vertexes.end(), newBatch.vertexes.begin(), newBatch.vertexes.end());
	//modify indexes to point to proper locations after the append
	for (GLuint& index : newBatch.indexes) {
		index += batch.indexes.size();
	}
	//append indexes
	batch.indexes.insert(batch.indexes.end(), newBatch.indexes.begin(), newBatch.indexes.end());
}

void IndexedRenderer::render() {
	//compile data
	uploadVbo();
	compileElementBuffer();
	//bind vertex array
	glBindVertexArray(vaoId);
	int offset = 0;
	for (auto entry : batches) {
		glBindTexture(GL_TEXTURE_2D, entry.first);
		glDrawElementsBaseVertex(GL_TRIANGLES, entry.second.indexes.size(), GL_UNSIGNED_INT, (void*)(sizeof(GLushort) * offset), offset);
		offset += entry.second.indexes.size();
	}
	//clean up
	batches.clear();
	glBindVertexArray(0);
}

void IndexedRenderer::uploadVbo() {
	compiledVbo.clear();
	for (auto entry : batches) {
		//add vertexes to total vbo
		compiledVbo.insert(compiledVbo.end(), entry.second.vertexes.begin(), entry.second.vertexes.end());
	}
	//upload vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * compiledVbo.size(), compiledVbo.data(), GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void IndexedRenderer::compileElementBuffer() {
	compiledIbo.clear();
	for (auto entry : batches) {
		//append the indexes
		compiledIbo.insert(compiledIbo.end(), entry.second.indexes.begin(), entry.second.indexes.end());
	}
	//upload ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * compiledIbo.size(), compiledIbo.data(), GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
