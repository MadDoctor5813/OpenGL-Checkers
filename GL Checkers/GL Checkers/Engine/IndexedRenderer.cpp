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
	shader.enable();
	camTransformLoc = glGetUniformLocation(shader.getProgram(), "camTransform");
	textureLoc = glGetUniformLocation(shader.getProgram(), "spriteTexture");
	glActiveTexture(GL_TEXTURE0);
}

void IndexedRenderer::draw(DrawBatch& batch, int depth) {
	if (batches.count(depth) == 0) { //batch vector for the passed depth doesn't exist
		batches.emplace(depth, std::vector<DrawBatch>()); //make a new one
	}
	batches.at(depth).push_back(batch); //add the batch to its respective vector
}

void IndexedRenderer::render(App& appRef) {
	//upload uniform data
	glUniformMatrix4fv(camTransformLoc, 1, GL_FALSE, &(appRef.getCamera().getMatrix()[0][0]));
	glUniform1i(textureLoc, 0);
	sortBatches();
	//compile data for buffers
	compileVbo();
	compileIbo();
	glBindVertexArray(vaoId);
	//upload buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * compiledVbo.size(), compiledVbo.data(), GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * compiledIbo.size(), compiledIbo.data(), GL_STREAM_DRAW);
	int iboOffset = 0;
	int baseVertex = 0;
	for (auto entry : batches) {
		int batchOffset = 0;
		GLuint lastTex = entry.second[0].texture;
		int indexCount = 0;
		for (auto batch = entry.second.begin(); batch != entry.second.end(); batch++) {
			indexCount += batch->indexes.size();
			if (batch->texture != lastTex || std::next(batch) == entry.second.end()) { //if the texture's changed, or we've reached the end
				makeDrawCall(indexCount, iboOffset + batchOffset, baseVertex, lastTex);
				indexCount = 0;
			}
			lastTex = batch->texture;
			batchOffset += batch->indexes.size();
			baseVertex += batch->vertexes.size();
		}
		iboOffset += batchOffset;
	}
	batches.clear();
	glBindVertexArray(0);
}

void IndexedRenderer::makeDrawCall(int count, int offset, int baseVertex, GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * offset), baseVertex);
}

void IndexedRenderer::sortBatches() {
	for (auto entry : batches) {
		///texture sort the batches in each depth batch
		std::stable_sort(entry.second.begin(), entry.second.end(), [](DrawBatch b1, DrawBatch b2) {return b1.texture < b2.texture; });
	}
}

void IndexedRenderer::compileVbo() {
	compiledVbo.clear();
	for (auto entry : batches) {
		for (auto batch : entry.second) {
			compiledVbo.insert(compiledVbo.end(), batch.vertexes.begin(), batch.vertexes.end());
		}
	}
}

void IndexedRenderer::compileIbo() {
	compiledIbo.clear();
	for (auto entry : batches) {
		int offset = 0;
		for (auto batch : entry.second) {
			for (GLuint& index : batch.indexes) {
				index += offset; //make indexes valid after insertion
			}
			//insert indexes
			compiledIbo.insert(compiledIbo.end(), batch.indexes.begin(), batch.indexes.end());
			offset += batch.indexes.size();
		}
	}
}