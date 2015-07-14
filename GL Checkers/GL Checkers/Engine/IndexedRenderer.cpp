#include "IndexedRenderer.h"

#include <iostream>
#include <algorithm>


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
	if (batches.count(texture) == 0) {
		//make a new vector
		batches.emplace(texture, std::vector<DrawBatch>());
	}
	//add the batch to the map
	batches.at(texture).push_back(newBatch);
}

void IndexedRenderer::render() {
	//combine the batches
	combineBatches();
	//compile data
	uploadVbo();
	compileIbo();
	//bind vertex array
	glBindVertexArray(vaoId);
	int offset = 0;
	for (auto entry : batches) {
		glBindTexture(GL_TEXTURE_2D, entry.first);
		glDrawElementsBaseVertex(GL_TRIANGLES, entry.second[0].indexes.size(), GL_UNSIGNED_INT, (void*)(sizeof(GLushort) * offset), offset);
		offset += entry.second[0].indexes.size();
	}
	//clean up
	batches.clear();
	glBindVertexArray(0);
}

void IndexedRenderer::combineBatches() {
	for (auto entry : batches) {
		//depth sort the batches
		std::stable_sort(entry.second.begin(), entry.second.end(), [](DrawBatch b1, DrawBatch b2) {return b1.depth < b2.depth; });
		DrawBatch combined;
		int indexOffset;
		for (auto batch : entry.second) {	
			//insert vertexes
			combined.vertexes.insert(combined.vertexes.end(), batch.vertexes.begin(), batch.vertexes.end());
			//modify indexes
			std::for_each(batch.indexes.begin(), batch.indexes.end(), [indexOffset](GLuint& index) {index += indexOffset; });
			//insert indexes
			combined.indexes.insert(combined.indexes.end(), batch.indexes.begin(), batch.indexes.end());
			indexOffset += batch.indexes.size();
		}
		entry.second.clear(); //clear out all the batches
		entry.second.push_back(combined); //insert new combined batch
	}
}

void IndexedRenderer::uploadVbo() {
	compiledVbo.clear();
	//compile vertexes
	for (auto entry : batches) {
		compiledVbo.insert(compiledVbo.end(), entry.second[0].vertexes.begin(), entry.second[0].vertexes.end());
	}
	//upload vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * compiledVbo.size(), compiledVbo.data(), GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void IndexedRenderer::compileIbo() {
	compiledIbo.clear();
	//compile indexes
	for (auto entry : batches) {
		compiledIbo.insert(compiledIbo.end(), entry.second[0].indexes.begin(), entry.second[0].indexes.end());
	}
	//upload ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * compiledIbo.size(), compiledIbo.data(), GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
